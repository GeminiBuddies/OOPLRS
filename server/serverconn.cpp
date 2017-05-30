#include "serverconn.h"

#include <QMessageBox>

ServerConn::ServerConn() {
    broadcastAddress = getBroadcastAddr();
    status = serverStatus::Closed;

    this->name = QString("anonymous server");
}

ServerConn::ServerConn(QObject *parent) : QObject(parent) { new (this)ServerConn(); }

void ServerConn::start(QString name) {
    if (status != serverStatus::Closed) return;

    this->name = name;

    threadListener = new ServerConnListener(this, this);
    threadListener->start();

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

    while (threadListener->isRunning()) ;
    delete threadListener;
    threadListener = nullptr;
}

void ServerConn::sendData(Conn dest, byteseq data, int length) {
    if (status == serverStatus::Closed) return;

    sendDataBySocket(clients[dest->id], data, length);
}

void ServerConn::broadcast(byteseq data, int length) {
    if (status == serverStatus::Closed) return;

    for (auto i : clients.values()) {
        sendDataBySocket(i, data, length);
    }
}

void ServerConn::socketReady() {
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());

    auto data = sock->readAll();
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

void ServerConn::socketDisconnected() {
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());

    if (removing.contains(sock)) return;

    emitOnClientDisconnected(conns[ids[sock]]);

    delete conns[ids[sock]];
    conns.remove(ids[sock]);
    clients.remove(ids[sock]);
    ids.remove(sock);
}

void ServerConn::sendDataBySocket(QTcpSocket *sock, byteseq data, int length) {
    sock->write(data, length);
    sock->flush();
}

void ServerConn::emitOnClientData(Conn remote, byteseq data, int length) { emit onClientData(remote, data, length); }
void ServerConn::emitOnClientConnected(Conn remote) { emit onClientConnected(remote); }
void ServerConn::emitOnClientDisconnected(Conn remote) { emit onClientDisconnected(remote); }

ServerConnListener::ServerConnListener(QObject *parent, ServerConn *conn) : QThread(parent), conn(conn) { ; }

void ServerConnListener::run() {
    qRegisterMetaType<byteseq>("byteseq");
    qRegisterMetaType<Conn>("Conn");
#ifdef _DEBUG
    auto dsock = new QUdpSocket();
    dsock->bind(6644);

    dsock->writeDatagram(QByteArray("started"), conn->broadcastAddress, 6655); qDebug() << "started";
#endif

    int counter = 8;

    auto v = new QTcpServer();
    v->setMaxPendingConnections(MaxPlayer);

    while (conn->status == ServerConn::serverStatus::Closed) ;

    v->listen(QHostAddress::AnyIPv4, ServerClientPort);
    while (conn->status != ServerConn::serverStatus::Closed) {
        if (v->waitForNewConnection(NetInterval)) {
            if (v->hasPendingConnections()) {
                auto sock = v->nextPendingConnection();

                if (conn->status != ServerConn::serverStatus::Listening) {
                    sock->disconnect(); sock->close();
                    continue;
                }

                // wait for the first package
                if (sock->waitForReadyRead(ConnectPackageTimeOut)) {
                    auto data = sock->readAll();
                    auto fr = LRSBasicLayerFrame::FromQByteArray(data);
                    if (fr.type != LRSBasicLayerFrame::frameType::Connect) {
                        sock->disconnect();
                        sock->close();
                    }

                    auto cnn = new _Conn();
                    cnn->name = QString(fr.data);
                    cnn->addr = sock->peerAddress();
                    cnn->id = counter++;

                    conn->clients.insert(cnn->id, sock);
                    conn->ids.insert(sock, cnn->id);
                    conn->conns.insert(cnn->id, cnn);

                    conn->emitOnClientConnected(cnn);

                    connect(sock, SIGNAL(readyRead()), conn, SLOT(socketReady()));
                    connect(sock, SIGNAL(disconnected()), conn, SLOT(socketDisconnected()));
                } else {
                    sock->disconnect();
                    sock->close();
                }
            }
        }
    }
}

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

    sock->writeDatagram(QByteArray(1, (char)(int)conn->status), conn->broadcastAddress, ServerBroadcastRecvPort);
    delete sock;
}
