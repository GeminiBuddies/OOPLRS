#ifndef IDIOT_H
#define IDIOT_H


#include "character.h"
class Idiot : public Character
{
    Q_OBJECT
public:
    using Character::Character;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:

};

#endif // IDIOT_H
