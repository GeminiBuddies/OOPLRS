#ifndef PIEDPIPER_H
#define PIEDPIPER_H

#include "character.h"
class PiedPiper : public Character
{
    Q_OBJECT
public:
    using Character::Character;
    void roleAct(QString str);

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void changeVoteStates(QString time, int delta);

};

#endif // PIEDPIPER_H
