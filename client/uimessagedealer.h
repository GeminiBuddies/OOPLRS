#ifndef UIMESSAGEDEALER_H
#define UIMESSAGEDEALER_H

#include "messagedealer.h"

class UiMessageDealer : public MessageDealer
{
    Q_OBJECT
public:
    using MessageDealer::MessageDealer;

public slots:
    void receiveMessage(QString str1,QString str2=0,QString str3=0,QString str4=0,QString str5=0);


};

#endif // UIMESSAGEDEALER_H
