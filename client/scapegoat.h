#ifndef SCAPEGOAT_H
#define SCAPEGOAT_H


#include "character.h"
class Scapegoat : public Character
{
    Q_OBJECT
public:
    using Character::Character;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

};

#endif // SCAPEGOAT_H
