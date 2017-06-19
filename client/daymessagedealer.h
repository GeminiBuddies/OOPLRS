﻿/*************************************************
 * 名称： daymessagedealer.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： DayMessageDealer类，负责处理游戏中白天的消息，并将消息传回Character类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef DAYMESSAGEDEALER_H
#define DAYMESSAGEDEALER_H

#include "messagedealer.h"
#include <QMap>

class DayMessageDealer : public MessageDealer
{
    Q_OBJECT
public:
    DayMessageDealer(Messager* player, MessageDealer* character);
    bool canVote=1;
    bool canCancelVote=0;

signals:
    void changeVoteStates(QString time,int delta);
    void judge(QString str1,QString str2);

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    void night();
    void chooseSheriff();
    void showSheriffCandidate(QString str);
    void determineSheriff(QString str);
    void showDied(QString str);
    void showLastWords(QString str1,QString str2);
    void startChat(QString str1);
    void showChatMessage(QString str1,QString str2);
    void win();
    void lose();
    void clicked(QString str1, QString str2);
    void startVote();
    void showVote(QString str1,QString str2);
    void showVoteResult(QString str1,QString str2);
    void showCharacter(QString str1,QString str2);
    void draw();
    void startLastWords(QString str);
    MessageDealer* character;
};

#endif // DAYMESSAGEDEALER_H
