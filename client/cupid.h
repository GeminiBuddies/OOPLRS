#ifndef CUPID_H
#define CUPID_H


#include "character.h"
class Cupid : public Character
{
    Q_OBJECT
public:
    using Character::Character;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void changeVoteStates(QString time, int delta);

};

#endif // CUPID_H
