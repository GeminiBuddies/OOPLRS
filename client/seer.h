#ifndef SEER_H
#define SEER_H

#include "character.h"
class Seer : public Character
{
    Q_OBJECT
public:
    using Character::Character;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    void showIdentity(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void roleAct(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

};

#endif // SEER_H
