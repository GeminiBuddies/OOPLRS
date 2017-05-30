#ifndef TOWNSFOLK_H
#define TOWNSFOLK_H

#include "character.h"
class Townsfolk : public Character
{
    Q_OBJECT
public:
    using Character::Character;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

};

#endif // TOWNSFOLK_H
