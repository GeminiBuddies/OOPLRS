#include "idiot.h"

void Idiot::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
    if(str1=="idiotKilledByVoting") idiotKilledByVoting();
}

void Idiot::idiotKilledByVoting(){
    for(int i=1;i<=20;i++){
        alive[i]=0;
        QString temp=QVariant(i).toString();
        emit sendMessageToDMDealer("notAlive", temp);
        emit sendMessageToNMDealer("notAlive", temp);
    }
    emit sendMessage(GAMEMESSAGE, QStringLiteral("你被公投，免去死亡惩罚，但在以后不可投票"));
}
