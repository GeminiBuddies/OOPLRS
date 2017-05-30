#ifndef MOUSEAREA_H
#define MOUSEAREA_H

#include "uiproxy.h"
#include <QVariant>

class MouseArea : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void mouseAreaEnabled(bool enabled);
    void connectSignal();

public slots:
    void onClicked();
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    bool isClicked=0;
    bool canBeVoted=0;
};

#endif // MOUSEAREA_H
