#include "scapegoat.h"

void Scapegoat::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
    if(str1=="canDetermine") canDetermine();
    else if(determine==1&&str1=="showVoteResult") determine=0;
}

void Scapegoat::canDetermine(){
    emit sendMessage(GAMEMESSAGE,QStringLiteral("你可以发动技能，选择下一轮可以投票的人"));
    determine=1;
}

void Scapegoat::changeVoteStates(QString time, int delta){
    static int vote=0;

    if(delta==0){//重置vote
        vote=0;
    }else{//更改vote
        vote+=delta;
    }

    if(determine==1){
        canVote(time,1);
        canCancelVote(time,1);
    }
    else{
        if(vote==1){
            canVote(time,0);
            canCancelVote(time,1);
        }else{
            canVote(time,1);
            canCancelVote(time,0);
        }
    }
}
