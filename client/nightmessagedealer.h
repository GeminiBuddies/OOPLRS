#ifndef NIGHTMESSAGEDEALER_H
#define NIGHTMESSAGEDEALER_H

#include "messagedealer.h"

class NightMessageDealer : public MessageDealer
{
    Q_OBJECT
public:
    NightMessageDealer(Messager* player, MessageDealer* character);
    bool canVote=1;
    bool canCancelVote=0;

signals:
    void changeVoteStates(QString time,int delta);

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    void day();
    void roleActEnd();
    void shotByCupid(QString str);
    void roleActLoseAbility();
    void clicked(QString str1,QString str2);
    void roleAct();
    void startVote();
    void showVote(QString str1,QString str2);
    void showVoteResult(QString str1,QString str2);
    void puzzledConfirm(QString str);
    void cannotVote();
    MessageDealer* character;

};

#endif // NIGHTMESSAGEDEALER_H
