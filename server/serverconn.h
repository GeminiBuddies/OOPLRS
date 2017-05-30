#ifndef SERVERCONN_H
#define SERVERCONN_H

#include "../cih/globalConf.h"

#include <QObject>
#include <QMap>
#include <QThread>
#include <QMessageBox>

class ServerConn : public QObject {
    Q_OBJECT

    friend class ServerConnBroadcaster;
    friend class ServerConnListener;
public:
    ServerConn();
    explicit ServerConn(QObject *parent);

    void start(QString name);
    void beginAcceptConnection();
    void endAcceptConnection();
    void close();

    void sendData(Conn dest, byteseq data, int length);

    void broadcast(byteseq data, int length);

signals:
    void onClientConnected(Conn remote);
    void onClientDisconnected(Conn remote);
    void onClientData(Conn remote, byteseq data, int length);

public slots:
    void socketReady();
    void socketDisconnected();

    void newConn(QTcpSocket *sock, QHostAddress addr, int id, QString name);

private:
    QString name;

    enum class serverStatus {
        Closed,
        Started,
        Listening,
    };

    serverStatus status;

    void sendDataBySocket(QTcpSocket *sock, byteseq data, int length);

    void emitOnClientConnected(Conn remote);
    void emitOnClientDisconnected(Conn remote);
    void emitOnClientData(Conn remote, byteseq data, int length);

    QHostAddress broadcastAddress;

    ServerConnBroadcaster *threadBroadcaster;
    ServerConnListener *threadListener;

    QMap<int, QTcpSocket*> clients;
    QMap<QTcpSocket*, int> ids;
    QMap<int, Conn> conns;
    QSet<QTcpSocket*> removing;

    QMap<QTcpSocket*, QByteArray> cache;

    void PkgHandler(QTcpSocket* sock);
};

// Sub-class definition
class ServerConnListener : public QThread {
    Q_OBJECT
public:
    ServerConnListener() = delete;
    explicit ServerConnListener(QObject *parent = 0);

    ServerConn::serverStatus status;
protected:
    void run();
signals:
    void onNewConn(QTcpSocket *sock, QHostAddress addr, int id, QString name);
};

class ServerConnBroadcaster : public QThread {
    Q_OBJECT
public:
    ServerConnBroadcaster() = delete;
    explicit ServerConnBroadcaster(QObject *parent = 0, ServerConn *conn = 0);
private :
    ServerConn *conn;
protected:
    void run();
};

#endif // SERVERCONN_H
