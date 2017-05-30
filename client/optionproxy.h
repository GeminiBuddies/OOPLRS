#ifndef OPTIONPROXY_H
#define OPTIONPROXY_H

#include "uiproxy.h"

class OptionProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    QObject *checkbox1, *checkbox2, *checkbox3;
    QObject *slider1,*slider2,*slider3;
    QObject *nameInput;
    QObject *confirmButton;
};

#endif // OPTIONPROXY_H
