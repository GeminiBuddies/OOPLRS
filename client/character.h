#ifndef CHARACTER_H
#define CHARACTER_H

#include "messagedealer.h"
#include "daymessagedealer.h"
#include "nightmessagedealer.h"

class Character : public MessageDealer
{
    Q_OBJECT
public:
    Character(Messager* player);

signals:
    void sendMessageToDMDealer(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void sendMessageToNMDealer(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void sendMessageToPlayer(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");


public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    virtual void changeVoteStates(QString time, int delta);
    virtual void die(QString str);

protected:
    QString time;
    bool isDied;
    QString number;
    bool flag=0;

    DayMessageDealer* DMDealer;
    NightMessageDealer* NMDealer;


    void changeTime(QString str);
    void win();
    void lose();
    void startVote();
    void canVote(QString time, bool b);
    void canCancelVote(QString time, bool b);
};

#endif // CHARACTER_H
