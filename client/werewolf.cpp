#include "werewolf.h"

void Werewolf::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
    if(str1=="roleAct"){
        if(flag==0){
            emit sendMessage(GAMEMESSAGE,QStringLiteral("狼人们出来活动了！"));
            flag=1;
        }
        QString temp="characterImage"+str2;
        emit sendMessage("dealer",temp,"changeRole","qrc:/images/images/werewolf.jpg");
    }else if(str1=="werewolfKill"){
        emit sendMessage(GAMEMESSAGE, QStringLiteral("最终决定为")+str2+QStringLiteral("号玩家"));
    }
}


