#include "nightmessagedealer.h"

NightMessageDealer::NightMessageDealer(Messager *player, MessageDealer *character):MessageDealer(player){
    this->character=character;
    for(int i=1;i<=20;i++){
        alive[i]=0;
    }
}

void NightMessageDealer::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1== "day")day();
    else if(str1=="alive") alive[QVariant(str2).toInt()]=1;
    else if(str1=="notAlive") alive[QVariant(str2).toInt()]=0;
    if(str1== "roleActEnd")roleActEnd();
    if(str1== "shotByCupid")shotByCupid(str2);
    if(str1== "roleActLoseAbility")roleActLoseAbility();
    if(str1== "startVote")startVote();
    if(str1== "vote")showVote(str3,str2);//交换了顺序
    if(str1== "cancelVote") cancelVote(str3);
    if(str1== "showVoteResult")showVoteResult(str2,str3);
    if(str1== "roleAct")roleAct();
    if(str1== "clicked")clicked(str2,str3);
    if(str1=="puzzledConfirm") puzzledConfirm(str2);
    if(str1=="cannotVote") cannotVote();
    else if(str1=="playerNum"){
        for(int i=1;i<=QVariant(str2).toInt();i++){
            alive[i]=1;
        }
    }
}

void NightMessageDealer::day(){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("天亮了，大家起床啦~"));
    emit sendMessage("dealer","day");
    emit sendMessage("changeTime","day");
    emit sendMessage("toServer","day");
    emit sendMessage("dealer", "hideBigText");
}

void NightMessageDealer::roleActEnd(){
    emit sendMessage("dealer", "roleActionEnd");
    emit sendMessage(GAMEMESSAGE, QStringLiteral("角色行动结束"));
    emit sendMessage("dealer", "showBigText", QStringLiteral("等待中"));
    canVote=1;
    canCancelVote=0;
    emit changeVoteStates("day",0);
}

void NightMessageDealer::shotByCupid(QString str){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("你被丘比特射中了！你的情侣是")+str+QStringLiteral("号玩家"));
}

void NightMessageDealer::roleActLoseAbility(){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("长老已死亡，你失去了能力"));
}


void NightMessageDealer::roleAct(){
    emit sendMessage("dealer","roleActionStart");
    emit sendMessage("dealer", "hideBigText");
}

void NightMessageDealer::startVote(){
    for(int i=0;i<20;i++){
        if(alive[i]){
            QString temp="characterImage"+QVariant(i).toString();
            emit sendMessage("dealer", temp, "mouseAreaEnabled");
        }
    }
}

void NightMessageDealer::showVote(QString str1, QString str2){
    QString temp="characterImage"+str1;
    emit sendMessage("dealer", temp, "showVote", str2);
}

void NightMessageDealer::cancelVote(QString str1){
    QString temp="characterImage"+str1;
    emit sendMessage("dealer", temp, "hideVote");
}

void NightMessageDealer::showVoteResult(QString str1, QString str2){
    emit sendMessage(GAMEMESSAGE, str1+QStringLiteral("号玩家投给了")+str2+QStringLiteral("号玩家"));
    QString temp="characterImage"+str1;
    emit sendMessage("dealer", temp, "hideVote");
    for(int i=0;i<20;i++){
        QString temp="characterImage"+QVariant(i).toString();
        emit sendMessage("dealer",temp,"mouseAreaDisabled");
    }
}

void NightMessageDealer::clicked(QString str1, QString str2){
    QString temp="";
    int x;
    char t;
    if(str1.length()==15){
        temp+=str1[14];
        x=QVariant(temp).toInt();
        t='a'+x;
    }

    else if(str1.length()==16){
        temp+=str1[14];
        temp+=str1[15];
        x=QVariant(temp).toInt();
        t='a'+x;
    }
    QString temp2="";
    temp2+=t;
    if(str2=="1"&&canVote==true){
        emit changeVoteStates("night",1);
        emit sendMessage("toServer","vote",temp2);
        emit sendMessage("dealer",str1,"finishClicked");
        emit sendMessage(GAMEMESSAGE, QStringLiteral("你选择了")+temp+QStringLiteral("号"));
    }
    else if(str2=="0"&&canCancelVote==true){
        emit changeVoteStates("night",-1);
        emit sendMessage("toServer","cancelVote",temp2);
        emit sendMessage("dealer",str1,"finishClicked");
        emit sendMessage(GAMEMESSAGE, QStringLiteral("你取消选择了")+temp+QStringLiteral("号"));
    }
}

void NightMessageDealer::puzzledConfirm(QString str){
    emit sendMessage("dealer","roleActionStart");
    emit sendMessage(GAMEMESSAGE, str+QStringLiteral("号被吹笛者迷惑了"));
}

void NightMessageDealer::cannotVote(){
    for(int i=0;i<20;i++){
        QString temp="characterImage"+QVariant(i).toString();
        emit sendMessage("dealer", temp, "mouseAreaDisabled");
    }
    emit sendMessage(GAMEMESSAGE, QStringLiteral("因白痴或替罪羊的选择，你无法投票"));
}
