#ifndef CLIENTCONN_H
#define CLIENTCONN_H

#include "../cih/globalConf.cpp"

#include <QObject>

class ClientConn : public QObject
{
    Q_OBJECT
public:
    explicit ClientConn(QObject *parent = 0);

    bool connect(Conn server);
    void disconnect();

    void sendData(byteseq data, int length);

signals:
    void onBroadcast(Conn sender, byteseq data, int length);
    void onServerData(byteseq data, int length);
};

#endif // CLIENTCONN_H
