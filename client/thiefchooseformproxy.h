#ifndef THIEFCHOOSEFORMPROXY_H
#define THIEFCHOOSEFORMPROXY_H


#include "uiproxy.h"

class ThiefChooseFormProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void thiefChoose(int i);

private:
    QObject* image1;
    QObject* image2;

};

#endif // THIEFCHOOSEFORMPROXY_H
