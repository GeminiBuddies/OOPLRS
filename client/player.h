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
    QString name;//自己的人物名字
    QString number;//自己的编号
    QString time="notInGame";
    BeforeStartMessageDealer* BSMDealer;
    Character* character;
    UiMessageDealer* uiMessageDealer;
    Client* client;

    void constructCharacter(QString role);
    void initialClient(QString str);
};


#endif // PLAYER_H
