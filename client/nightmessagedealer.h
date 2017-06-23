/*************************************************
 * 名称： nightmessagedealer.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： NightMessageDealer类（MessageDealer派生类）。该类负责处理游戏开始后时间为“夜晚”时服务器和客户端UI发来的消息
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

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
    void cancelVote(QString str1);
    void showVoteResult(QString str1,QString str2);
    void puzzledConfirm(QString str);
    void cannotVote();
    void showPuzzled(QString str);
    MessageDealer* character;
    bool alive[21];
    QString number;//玩家编号
};

#endif // NIGHTMESSAGEDEALER_H
