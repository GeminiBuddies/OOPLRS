#include "witch.h"

void Witch::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
    if(str1=="roleAct"){
        roleAct(str2,str3);
    }
}

void Witch::roleAct(QString str1, QString str2){
    if(isDied) return;
    QChar a=*(str2.data());
    QChar b=*(str2.data()+1);
    emit sendMessage(GAMEMESSAGE, QStringLiteral("本回合被杀的是")+str1+QStringLiteral("号玩家。")
        +QStringLiteral("你还有")+a+QStringLiteral("瓶毒药，")+b+QStringLiteral("瓶解药，")+QStringLiteral("请选择是否使用"));
    QString temp1="";
    temp1+=a;
    QString temp2="";
    temp2+=b;
    emit sendMessage("dealer", "witchAct",a,b);
}
