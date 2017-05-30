#ifndef CHATBOXPROXY_H
#define CHATBOXPROXY_H

#include"uiproxy.h"

class ChatBoxProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();
    void showChatMessage(QString str);

public slots:
    void sendChatMessage(QString str);
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    QObject* sendBox;

};

#endif // CHATBOXPROXY_H
