#include "serverconn.h"

#include <QMessageBox>

ServerConn::ServerConn() {
    broadcastAddress = getBroadcastAddr();
    status = serverStatus::Closed;

    this->name = QString("anonymous server");

    connect(this, SIGNAL(_onReqBroadcast(byteseq, int)), this, SLOT(_broadcast(byteseq, int)));
    connect(this, SIGNAL(_onReqSendData(Conn, byteseq, int)), this, SLOT(_sendData(Conn, byteseq, int)));
}

ServerConn::ServerConn(QObject *parent) : QObject(parent) { new (this)ServerConn(); }

void ServerConn::start(QString name) {
    if (status != serverStatus::Closed) return;

    this->name = name;

    counter = 8;

    serv = new QTcpServer(this);
    connect(serv, SIGNAL(newConnection()), this, SLOT(newConn()));

    serv->setMaxPendingConnections(MaxPlayer);
    serv->listen(QHostAddress::AnyIPv4, ServerClientPort);

    status = serverStatus::Started;
}

void ServerConn::beginAcceptConnection() {
    if (status != serverStatus::Started) return;

    threadBroadcaster = new ServerConnBroadcaster(this, this);
    threadBroadcaster->start();

    status = serverStatus::Listening;
}

void ServerConn::endAcceptConnection() {
    if (status != serverStatus::Listening) return;
    status = serverStatus::Started;

    while (threadBroadcaster->isRunning()) ;

    delete threadBroadcaster;
    threadBroadcaster = nullptr;
}

void ServerConn::close() {
    if (status == serverStatus::Closed) return;
    if (status == serverStatus::Listening) endAcceptConnection();

    status = serverStatus::Closed;

    serv->disconnect();
    serv->close();
    delete serv;

    for (auto i : clients.values()) {
        i->disconnect();
    }
}

void ServerConn::sendData(Conn dest, byteseq data, int length) { emit _onReqSendData(dest, data, length); }
void ServerConn::_sendData(Conn dest, byteseq data, int length) {
    if (status == serverStatus::Closed) return;

    sendDataBySocket(clients[dest->id], data, length);
}

void ServerConn::broadcast(byteseq data, int length) { emit _onReqBroadcast(data, length); }
void ServerConn::_broadcast(byteseq data, int length) {
    if (status == serverStatus::Closed) return;

    for (auto i : clients.values()) {
        sendDataBySocket(i, data, length);
    }
}

void ServerConn::socketReady() {
    qDebug() << "recv";
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());

    auto data = sock->readAll();
    qDebug() << data;

    if (!cache.contains(sock)) cache.insert(sock, QByteArray());
    cache[sock].append(data);

    PkgHandler(sock);
    qDebug() << sock->isOpen() << sock->isValid();
}

void ServerConn::PkgHandler(QTcpSocket* sock) {
    int lastEnd = -1;

    for (;;) {
        int idx = cache[sock].indexOf(PkgSeperator);
        if (-1 == idx) break;

        auto data = cache[sock].mid(lastEnd + 1, idx - lastEnd - 1);
        lastEnd = idx;
        cache[sock][idx] = '%';

        auto fr = LRSBasicLayerFrame::FromQByteArray(data);

        if (fr.type == LRSBasicLayerFrame::frameType::Data) {
            emitOnClientData(conns[ids[sock]], data.constData(), data.size());
        } else if (fr.type == LRSBasicLayerFrame::frameType::Disconnect) {
            removing += sock;

            sock->disconnectFromHost();
            sock->close();

            emitOnClientDisconnected(conns[ids[sock]]);

            delete conns[ids[sock]];
            conns.remove(ids[sock]);
            clients.remove(ids[sock]);
            ids.remove(sock);
        }
    }

    if (lastEnd != -1) cache[sock] = cache[sock].right(cache[sock].size() - lastEnd - 1);
}

void ServerConn::socketDisconnected() {
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());

    if (removing.contains(sock)) return;

    emitOnClientDisconnected(conns[ids[sock]]);

    delete conns[ids[sock]];
    conns.remove(ids[sock]);
    clients.remove(ids[sock]);
    ids.remove(sock);
}

void ServerConn::newConn() {
    auto sock = serv->nextPendingConnection();

    if (status != ServerConn::serverStatus::Listening) {
        sock->disconnectFromHost(); sock->close();
        return;
    }

    // wait for the first package

    if (sock->waitForReadyRead(ConnectPackageTimeOut)) {
        auto data = sock->readAll();
        auto fr = LRSBasicLayerFrame::FromQByteArray(data);
        if (fr.type != LRSBasicLayerFrame::frameType::Connect) {
            sock->disconnect();
            sock->close();
        }

        auto id = counter++;

        auto cnn = new _Conn();
        cnn->name = QString(fr.data);
        //cnn->name = QString("123");
        cnn->addr = sock->peerAddress();
        cnn->id = id;

        clients.insert(id, sock);
        ids.insert(sock, id);
        conns.insert(id, cnn);

        emitOnClientConnected(cnn);

        connect(sock, SIGNAL(readyRead()), this, SLOT(socketReady()));
        connect(sock, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

    } else {
        sock->disconnect();
        sock->close();
    }
}

void ServerConn::sendDataBySocket(QTcpSocket *sock, byteseq data, int length) {
    QByteArray buff = QByteArray(data, length);
    buff.append(PkgSeperator);
    sock->write(buff);
    sock->flush();
}

void ServerConn::emitOnClientData(Conn remote, byteseq data, int length) { emit onClientData(remote, data, length); }
void ServerConn::emitOnClientConnected(Conn remote) { emit onClientConnected(remote); }
void ServerConn::emitOnClientDisconnected(Conn remote) { emit onClientDisconnected(remote); }

ServerConnBroadcaster::ServerConnBroadcaster(QObject *parent, ServerConn *conn) : QThread(parent), conn(conn) { ; }

void ServerConnBroadcaster::run() {
    auto sock = new QUdpSocket();
    sock->bind(ServerBroadcastSendPort);
    QByteArray temp; temp.append(conn->name);
    auto fr = LRSBasicLayerFrame(LRSBasicLayerFrame::frameType::Broadcast, temp);
    auto data = fr.ToQByteArray();

    while (conn->status != ServerConn::serverStatus::Listening) ;

    while (conn->status == ServerConn::serverStatus::Listening) {
        sock->writeDatagram(data, conn->broadcastAddress, ServerBroadcastRecvPort);
        sock->waitForBytesWritten();

        sleep(ServerBroadcastInterval);
    }

    delete sock;
}
