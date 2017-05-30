#ifndef GAMERECORDERPROXY_H
#define GAMERECORDERPROXY_H

#include "uiproxy.h"

class GameRecorderProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:
    void sendGameMessage(QVariant str);

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");


};

#endif // GAMERECORDERPROXY_H
