#ifndef BEFORESTARTMESSAGEDEALER_H
#define BEFORESTARTMESSAGEDEALER_H

#include "messagedealer.h"

class BeforeStartMessageDealer : public MessageDealer
{
    Q_OBJECT
public:
    using MessageDealer::MessageDealer;

public slots:
    void receiveMessage(QString str1,QString str2=0,QString str3=0,QString str4=0,QString str5=0);


};

#endif // BEFORESTARTMESSAGEDEALER_H
