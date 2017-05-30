#ifndef SERVERLISTPROXY_H
#define SERVERLISTPROXY_H

#include "uiproxy.h"
#include <QVector>

class ServerListProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void connectServerSucceed();
    void connectServer(int index);
    void getServer();

private:
    QObject* confirmButton;
    QObject* refreshButton;
    QVector<QString> serverList;
    void setServerList(QString str);
    void serverListHide();
};

#endif // SERVERLISTPROXY_H
