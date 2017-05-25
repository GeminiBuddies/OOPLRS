#ifndef SERVERCONN_H
#define SERVERCONN_H

#include "../cih/globalConf.cpp"

#include <QObject>
#include <QThread>

class ServerConn : public QObject {
    Q_OBJECT

    friend class ServerConnBroadcaster;
    friend class ServerConnListener;
public:
    explicit ServerConn(QObject *parent = 0);

    void start();
    void beginAcceptConnection();
    void endAccecptConnection();
    void close();

    void sendData(Conn dest, byteseq data, int length);

    void broadcast(byteseq data, int length);

signals:
    void onClientConnected(Conn remote);
    void onClientDisconnected(Conn remote);
    void onClientData(Conn remote, byteseq data, int length);

private:
    void emitOnClientConnected(Conn remote);
    void emitOnClientDisconnected(Conn remote);
    void emitOnClientData(Conn remote, byteseq data, int length);
};

// Sub-class definition
class ServerConnListener : public QThread {
    Q_OBJECT
public:
    explicit ServerConnListener(QObject *parent = 0, ServerConn *conn = 0);
private:
    ServerConn *conn;
protected:
    void run();
};

class ServerConnBroadcaster : public QThread {
    Q_OBJECT
public:
    explicit ServerConnBroadcaster(QObject *parent = 0, ServerConn *conn = 0);
private :
    ServerConn *conn;
protected:
    void run();
};

#endif // SERVERCONN_H
