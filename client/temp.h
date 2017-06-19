#ifndef TEMP_H
#define TEMP_H


#include"uiproxy.h"

class Temp : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

public slots:
    void sendChatMessage(QString str);
    void receiveMessage(QString str1,QString str2,QString str3,QString str4,QString str5);

private:
    QObject* sendBox;

};

#endif // TEMP_H
