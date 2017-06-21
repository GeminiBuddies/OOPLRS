/*************************************************
 * 名称： character.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： Character抽象类，有多个派生类，负责将游戏开始后的服务器和客户端UI消息
 *          根据发送时间传给DayMessageDealer和NightMessageDealer两个具体处理消息的类，
 *          并接收它们传回的消息，将其传给Player类。该类自身也会实际处理一些游戏消息。
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef CHARACTER_H
#define CHARACTER_H

#include "messagedealer.h"
#include "daymessagedealer.h"
#include "nightmessagedealer.h"

class Character : public MessageDealer
{
    Q_OBJECT
public:
    Character(Messager* player, QString number);

signals:
    void sendMessageToDMDealer(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void sendMessageToNMDealer(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void sendMessageToPlayer(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");


public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    virtual void changeVoteStates(QString time, int delta);
    virtual void judge(QString str1,QString str2);
    void noLastWords();

protected:
    QString time;
    bool isDied;
    QString number;
    bool flag=0;
    bool alive[21];//当前活着的人
    bool lastWords = 1;//被狼人杀死是否还有遗言

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
