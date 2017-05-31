#include "serverconn.h"

#include <QMessageBox>

ServerConn::ServerConn() {
    broadcastAddress = getBroadcastAddr();
    status = serverStatus::Closed;

    this->name = QString("anonymous server");

    connect(this, SIGNAL(_onReqSend()), this, SLOT(_send()));
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

ServerConn::sendCacheFr::sendCacheFr(QTcpSocket *r, QByteArray d) : remote(r), data(d) { ; }

void ServerConn::sendData(Conn dest, byteseq data, int length) {
    if (status == serverStatus::Closed) return;

    sendCacheLock.lock();
    sendCache.enqueue(sendCacheFr(clients[dest->id], QByteArray(data, length)));
    sendCacheLock.unlock();

    emit _onReqSend();
}

void ServerConn::_send() {
    sendCacheLock.lock();

    while (!sendCache.empty()) {
        auto v = sendCache.dequeue();
        sendDataBySocket(v.remote, v.data);
    }

    sendCacheLock.unlock();
}

void ServerConn::broadcast(byteseq data, int length) {
    if (status == serverStatus::Closed) return;

    auto v = QByteArray(data, length);

    sendCacheLock.lock();
    for (auto i : clients.values()) {
        sendCache.enqueue(sendCacheFr(i, v));
    }
    sendCacheLock.unlock();

    emit _onReqSend();
}

void ServerConn::socketReady() {
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());

    auto data = sock->readAll();

    if (!cache.contains(sock)) cache.insert(sock, QByteArray());
    cache[sock].append(data);

    PkgHandler(sock);
}

void ServerConn::PkgHandler(QTcpSocket* sock) {
    int lastEnd = -1;

    for (;;) {
        int idx = cache[sock].indexOf(PkgSeperator);
        if (-1 == idx) break;

        auto data = cache[sock].mid(lastEnd + 1, idx - lastEnd - 1);
        lastEnd = idx;
        cache[sock][idx] = '%';

        emitOnClientData(conns[ids[sock]], data.constData(), data.size());
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

void ServerConn::sendDataBySocket(QTcpSocket *sock, QByteArray data) {
    qDebug() << "To " << sock->peerAddress() << ":" << data;

    data.append(PkgSeperator);
    sock->write(data);
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
