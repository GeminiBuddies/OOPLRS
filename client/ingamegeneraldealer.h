#ifndef INGAMEGENERALDEALER_H
#define INGAMEGENERALDEALER_H

#include "messagedealer.h"

class InGameGeneralDealer : public MessageDealer
{
public:
    using MessageDealer::MessageDealer;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

};

#endif // INGAMEGENERALDEALER_H
