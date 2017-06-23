/*************************************************
 * 名称： player.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： Player类（Messager类的派生类），在客户端窗口开启时即创建，负责以下功能：
 *  1. 实例化一个Client类对象，负责与服务器连接
 *  2. 接收服务器发来的消息，将消息分类传给BeforeMessageDealer，Character，UiMessageDealer类处理
 *  3. 接收上述三个类处理后返回的消息，将消息传给UiProxy的各个派生类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "messager.h"
#include"character.h"
#include"mainwindowproxy.h"
#include "uiproxy.h"
#include "beforestartmessagedealer.h"
#include "werewolf.h"
#include "ancient.h"
#include "cupid.h"
#include "hunter.h"
#include "idiot.h"
#include "savior.h"
#include "scapegoat.h"
#include "seer.h"
#include "townsfolk.h"
#include "witch.h"
#include "thief.h"
#include "dead.h"
#include "piedpiper.h"
#include "uimessagedealer.h"
#include "client.h"

class Player : public Messager
{
    Q_OBJECT
public:
    UiProxy* ui;
    Player();
    void serverToUi(QString str1,QString str2="",QString str3="");



signals:
    void sendMessageToBSMDealer(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void sendMessageToCharacter(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void sendMessageToServer(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void sendMessageToUiDealer(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    QString name="deafult";//自己的人物名字
    QString sex="male";//性别
    QString number;//自己的编号
    QString time="notInGame";
    BeforeStartMessageDealer* BSMDealer;
    Character* character;
    UiMessageDealer* uiMessageDealer;
    Client* client;
    int playerNum=0;

    void constructCharacter(QString role);
    void initialClient(QString str);
    void changeRole(QString str);
    void getInfo();
};


#endif // PLAYER_H
