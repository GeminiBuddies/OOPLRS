#include "thief.h"

void Thief::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
    if(str1=="roleAct"){
        emit sendMessage(GAMEMESSAGE, QStringLiteral("请从三个角色中选出你想要的"));
        emit sendMessage("dealer","thiefAct",str2,str3);
    }
}
