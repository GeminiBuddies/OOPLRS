#ifndef CLIENTCONN_H
#define CLIENTCONN_H

#include "../cih/globalConf.cpp"

#include <QObject>
#include <QSet>

class ClientConn : public QObject
{
    Q_OBJECT
public:
    explicit ClientConn(QObject *parent = 0);

    bool connect(Conn server);
    void disconnect();

    void sendData(byteseq data, int length);

    typedef const QSet<Conn>* ServerList;
    ServerList getServers();

signals:
    void onServerData(byteseq data, int length);
    void onServerDisconnect();
};

#endif // CLIENTCONN_H
