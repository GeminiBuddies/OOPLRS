#ifndef CLIENTCONN_H
#define CLIENTCONN_H

#include "../cih/globalConf.h"

#include <QObject>
#include <QSet>
#include <QThread>

class ClientConn : public QObject
{
    Q_OBJECT
    friend class ClientConnListener;
public:
    ClientConn();
    explicit ClientConn(QObject *parent);

    void start(QString name);
    bool connect(Conn server);
    void disconnect();
    void close();

    void sendData(byteseq data, int length);

    typedef const QSet<Conn>* ServerList;
    ServerList getServers();

signals:
    void onServerData(byteseq data, int length);
    void onServerDisconnect();

private:
    enum class clientStatus {
        Closed,
        Started,
        Connected,
    };

    clientStatus status;

    QSet<Conn> servers;
    QTcpSocket *sock;

    ClientConnListener *threadListener;

    QString name;
};

class ClientConnListener : public QThread {
    Q_OBJECT
public:
    ClientConnListener() = delete;
    ClientConnListener(QObject *parent, ClientConn *conn);
private:
    ClientConn *conn;
protected:
    void run();
};

#endif // CLIENTCONN_H
