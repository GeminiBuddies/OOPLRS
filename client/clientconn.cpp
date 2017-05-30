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

    threadListener = new ClientConnListener();
    threadListener->start();

    status = clientStatus::Started;

    this->name = name;
}

bool ClientConn::connect(Conn server) {
    if (status != clientStatus::Started) return false;

    sock = new QTcpSocket();
    sock->connectToHost(server->addr, ServerClientPort);

    if (sock->waitForConnected(ConnectPackageTimeOut)) {
        auto fr = LRSBasicLayerFrame(LRSBasicLayerFrame::frameType::Data, QByteArray(name));
        sock->write(fr);

        status = clientStatus::Connected;
        while (threadListener->isRunning()) ;
        delete threadListener;
        threadListener = nullptr;

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

    threadListener = new ClientConnListener();
    threadListener->start();

    status = clientStatus::Started;
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

    sock->write(data, length);
}

ClientConn::ServerList ClientConn::getServers() {
    return &servers;
}

ClientConnListener::ClientConnListener(QObject *parent, ClientConn *conn) : QThread(parent), conn(conn) { ; }

void ClientConnListener::run() {
    int counter = 8;
    QUdpSocket* recv = new QUdpSocket(this);

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

                int id = counter++;
                QString name = QString(fr.data);

                auto cnn = new _Conn;
                cnn->id = id; cnn->name = name; cnn->addr = serverAddr;

                conn->servers.insert(cnn);
            }
        }
    }

    delete recv;
}
