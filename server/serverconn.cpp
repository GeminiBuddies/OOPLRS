#include "serverconn.h"

ServerConn::ServerConn(QObject *parent) : QObject(parent) {

}

void ServerConn::beginAcceptConnection() {

}


ServerConnListener::ServerConnListener(QObject *parent, ServerConn *conn) : QThread(parent), conn(conn) {

}

ServerConnBroadcaster::ServerConnBroadcaster(QObject *parent, ServerConn *conn) : QThread(parent), conn(conn)  {

}
