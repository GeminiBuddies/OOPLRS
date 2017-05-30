#ifndef WITCHCHOOSEFORMPROXY_H
#define WITCHCHOOSEFORMPROXY_H

#include "uiproxy.h"

class WitchChooseFormProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:
    void witchAct();

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void witchChoose(int i);

private:
    QObject* button1;
    QObject* button2;

};

#endif // WITCHCHOOSEFORMPROXY_H
