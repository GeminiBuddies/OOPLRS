#include "hunter.h"

void Hunter::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
    if(str1=="canShoot"){
        emit sendMessage(GAMEMESSAGE,"你可以发动技能，选择一个人和你一块死~");
    }else if(str1=="cannotShoot"){
        emit sendMessage(GAMEMESSAGE,"你无法发动技能");
    }
}
