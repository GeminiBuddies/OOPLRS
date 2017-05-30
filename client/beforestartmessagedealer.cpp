#include "beforestartmessagedealer.h"

void BeforeStartMessageDealer::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1=="join"){
        QString temp="characterImage"+str3;
        emit sendMessage("dealer", temp,"changeName", str2);
        emit sendMessage("dealer", temp, "changeImage", "qrc:/images/images/man1.png");
        emit sendMessage("dealer", temp, "changeRole", "qrc:/images/images/townsfolk.jpg");
        emit sendMessage(GAMEMESSAGE,str2+QStringLiteral("进入了游戏"));
        emit sendMessage("dealer", temp, "canBeVoted");
    }
    else if(str1=="setImage"){
        QString temp="characterImage"+str2;
        emit sendMessage("dealer", temp, "changeImage", str3);
    }
    else if(str1=="assignRoles"){
        QString temp="characterImage"+str3;
        emit sendMessage("dealer", temp, "changeRole", "qrc:/images/images/"+str2+".jpg");
        emit sendMessage(GAMEMESSAGE,QStringLiteral("您的身份是")+str2);
        emit sendMessage("time", "day");
    }
}
