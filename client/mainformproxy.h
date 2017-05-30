#ifndef MAINFORMPROXY_H
#define MAINFORMPROXY_H

#include "uiproxy.h"
#include "QPropertyAnimation"

class MainFormProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void nightAnimation();
    void dayAnimation();
    void roleActionStartAnimation();
    void roleActionEndAnimation();

private:
    QObject* weather=0;
    QObject* day=0;
    QObject* night=0;
    QObject* roleActionStart=0;
    QObject* roleActionEnd=0;
};

#endif // MAINFORMPROXY_H
