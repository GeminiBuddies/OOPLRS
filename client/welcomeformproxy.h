#ifndef WELCOMEFORMPROXY_H
#define WELCOMEFORMPROXY_H

#include "uiproxy.h"

class WelcomeFormProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void getPlayerSetting(QString name, bool sex);
};

#endif // WELCOMEFORMPROXY_H
