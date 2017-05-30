#ifndef WITCH_H
#define WITCH_H

#include "character.h"
class Witch : public Character
{
    Q_OBJECT
public:
    using Character::Character;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    void roleAct(QString str1,QString str2);
};

#endif // WITCH_H
