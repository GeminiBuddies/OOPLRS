#ifndef SHERIFFCHOOSEFORMPROXY_H
#define SHERIFFCHOOSEFORMPROXY_H

#include "uiproxy.h"

class SheriffChooseFormProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void sheriffChoose(int i);

private:

};



#endif // SHERIFFCHOOSEFORMPROXY_H
