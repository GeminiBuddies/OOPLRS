#include "clientconn.h"

ClientConn::ClientConn() {
    status = clientStatus::Closed;
    sock = nullptr;
}

ClientConn::ClientConn(QObject *parent) : QObject(parent) {
    new (this) ClientConn();
}

void ClientConn::start(QString name) {
    if (status != clientStatus::Closed) return;

    threadListener = new ClientConnListener(this, this);
    threadListener->start();

    status = clientStatus::Started;

    this->name = name;
}

bool ClientConn::connect(Conn server) {
    if (status != clientStatus::Started) return false;

    sock = new QTcpSocket();
    sock->connectToHost(server->addr, ServerClientPort);

    if (sock->waitForConnected(ConnectPackageTimeOut)) {
        QByteArray temp; temp.append(name);
        auto fr = LRSBasicLayerFrame(LRSBasicLayerFrame::frameType::Connect, temp);
        sock->write(fr.ToQByteArray().data());
        sock->flush();

        status = clientStatus::Connected;
        while (threadListener->isRunning()) ;
        delete threadListener;
        threadListener = nullptr;

        QObject::connect(sock, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

        return true;
    } else {
        delete sock;
        sock = nullptr;

        return false;
    }
}

void ClientConn::disconnect() {
    if (status != clientStatus::Connected) return;

    sock->disconnectFromHost();
    sock->close();

    delete sock;
    sock = nullptr;

    threadListener = new ClientConnListener(this, this);
    threadListener->start();

    status = clientStatus::Started;
}

void ClientConn::onReadyRead() {
    cache.append(sock->readAll());
    PkgHandler();
}

void ClientConn::PkgHandler() {
    int lastEnd = -1;

    for (;;) {
        int idx = cache.indexOf(PkgSeperator);
        if (-1 == idx) break;

        auto data = cache.mid(lastEnd + 1, idx - lastEnd - 1);
        lastEnd = idx;
        cache[idx] = '%';

        emit onServerData(data.data(), data.length());
    }

    if (lastEnd != -1) cache = cache.right(cache.size() - lastEnd - 1);
}

void ClientConn::close() {
    if (status == clientStatus::Closed) return;
    if (status == clientStatus::Connected) { disconnect(); return; }

    status = clientStatus::Closed;
    while (threadListener->isRunning()) ;
    delete threadListener;
    threadListener = nullptr;
}

void ClientConn::sendData(byteseq data, int length) {
    if (status != clientStatus::Connected) return;

    auto buf = QByteArray(data, length);
    buf.append(PkgSeperator);
    sock->write(buf);
}

ClientConn::ServerList ClientConn::getServers() {
    return &servers;
}

ClientConnListener::ClientConnListener(QObject *parent, ClientConn *conn) : QThread(parent), conn(conn) { ; }

void ClientConnListener::run() {
    int counter = 8;
    QUdpSocket* recv = new QUdpSocket();

    while (conn->status != ClientConn::clientStatus::Started) ;

    recv->bind(ServerBroadcastRecvPort);

    while (conn->status == ClientConn::clientStatus::Started) {
        if (recv->waitForReadyRead(ServerBroadcastRecvInterval)) {
            if (recv->hasPendingDatagrams()) {
                auto data = QByteArray();
                QHostAddress serverAddr;
                data.resize(recv->pendingDatagramSize());
                recv->readDatagram(data.data(), data.size(), &serverAddr);

                auto fr = LRSBasicLayerFrame::FromQByteArray(data);
                if (fr.type != LRSBasicLayerFrame::frameType::Broadcast) continue;

                if (conn->host.contains(serverAddr)) break;

                int id = counter++;
                QString name = QString(fr.data);

                auto cnn = new _Conn;
                cnn->id = id; cnn->name = name; cnn->addr = serverAddr;

                conn->servers.insert(cnn);
                conn->host.insert(serverAddr);
            }
        }
    }

    delete recv;
}
