#include "character.h"

Character::Character(Messager *player, QString number):MessageDealer(player){
    DMDealer=new DayMessageDealer(player,this);
    NMDealer=new NightMessageDealer(player,this);
    QObject::connect(this,SIGNAL(sendMessageToDMDealer(QString,QString,QString,QString,QString)),DMDealer,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(this,SIGNAL(sendMessageToNMDealer(QString,QString,QString,QString,QString)),NMDealer,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(DMDealer,SIGNAL(changeVoteStates(QString,int)),this,SLOT(changeVoteStates(QString,int)));
    QObject::connect(NMDealer,SIGNAL(changeVoteStates(QString,int)),this,SLOT(changeVoteStates(QString,int)));
    QObject::connect(DMDealer,SIGNAL(judge(QString,QString)),this,SLOT(die(QString,QString)));
    time="day";
    this->number=number;
}


void Character::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1=="dealer"){
        sendMessage(str1,str2,str3,str4,str5);
    }else if(str1=="changeTime"){
        changeTime(str2);
    }else if(str1=="ui"){
        sendMessageToPlayer(str1,str2,str3,str4,str5);
    }else if(time=="day"){
        sendMessageToDMDealer(str1,str2,str3,str4,str5);
        flag=0;
    }else if(time=="night"){
        sendMessageToNMDealer(str1,str2,str3,str4,str5);
    }
}



void Character::changeTime(QString str){
    time = str;
    emit sendMessage("time", time);
}

void Character::canVote(QString time,bool b){
    if(time=="day")
        DMDealer->canVote=b;
    else
        NMDealer->canVote=b;
}

void Character::canCancelVote(QString time, bool b){
    if(time=="day")
        DMDealer->canCancelVote=b;
    else
        NMDealer->canCancelVote=b;
}

void Character::changeVoteStates(QString time, int delta){
    static int vote=0;

    if(delta==0){//重置vote
        vote=0;
    }else{//更改vote
        vote+=delta;
    }

    if(vote==1){
        canVote(time,0);
        canCancelVote(time,1);
    }else{
        canVote(time,1);
        canCancelVote(time,0);
    }
}

void Character::die(QString str1, QString str2){
    if(str1==number)
        if(str2=="1"){
            emit sendMessage(GAMEMESSAGE,QStringLiteral("你死了"));
            emit sendMessage(GAMEMESSAGE, QStringLiteral("请发表遗言"));
            emit sendMessage("dealer", "showBigText", QStringLiteral("请发表遗言"));
            emit sendMessage("dealer", "canChat");
        }else if(str2=="0"){
            emit sendMessage("dealer", "canChat");
            emit sendMessage(GAMEMESSAGE, QStringLiteral("请发言"));
            emit sendMessage("dealer", "showBigText", QStringLiteral("请发言"));
        }
}



