#ifndef MAINWINDOWPROXY_H
#define MAINWINDOWPROXY_H

#include "uiproxy.h"

class MainWindowProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

};

#endif // MAINWINDOWPROXY_H
