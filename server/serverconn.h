#ifndef SERVERCONN_H
#define SERVERCONN_H

#include "../cih/globalConf.cpp"

#include <QObject>

class ServerConn : public QObject
{
    Q_OBJECT
public:
    explicit ServerConn(QObject *parent = 0);

    void beginAcceptConnection();
    void endAccecptConnection();

    void sendData(Conn dest, byteseq data, int length);

signals:
    void onClientConnected(Conn remote);
    void onClientDisconnected(Conn remote);
    void onClientData(Conn remote, byteseq data, int length);
};

#endif // SERVERCONN_H
