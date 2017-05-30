#include "savior.h"

void Savior::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
    if(str1=="roleAct"){
        if(str2!="0"){
            emit sendMessage(GAMEMESSAGE, QStringLiteral("请选择一个人守护，不可选择与上回合相同的人。你上回合选择了")+str2+QStringLiteral("号玩家"));
        }else{
            emit sendMessage(GAMEMESSAGE, QStringLiteral("请选择一个人守护"));
        }

    }
}
