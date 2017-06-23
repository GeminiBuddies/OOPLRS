#include "seer.h"

void Seer::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
    if(str1=="roleAct")
        roleAct(str1,str2,str3,str4,str5);
    else if(str1=="showIdentity")
        showIdentity(str1,str2,str3,str4,str5);
}

void Seer::roleAct(QString str1, QString str2, QString str3, QString str4, QString str5){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("请选择要查验的玩家"));
}

void Seer::showIdentity(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str3=="0"){
        emit sendMessage(GAMEMESSAGE, QStringLiteral("该玩家是狼人"));
        QString temp="characterImage"+str2;
        emit sendMessage("dealer",temp,"changeRole", "qrc:/images/images/werewolf.jpg");
    }
    else{
        emit sendMessage(GAMEMESSAGE, QStringLiteral("该玩家是好人"));
        QString temp="characterImage"+str2;
        emit sendMessage("dealer",temp,"changeRole", "qrc:/images/images/townsfolk.jpg");
    }
  /*  QString temp="characterImage"+str2;
    emit sendMessage("dealer",temp,"changeRole", "qrc:/images/images/"+str3+".jpg");*/
}
