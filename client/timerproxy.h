#ifndef TIMERPROXY_H
#define TIMERPROXY_H

#include "uiproxy.h"

class TimerProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    QObject* timer;
    QObject* text;
    QObject* attrs;
    void startTimer(int time);
};


#endif // TIMERPROXY_H
