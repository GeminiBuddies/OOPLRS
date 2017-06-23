#include "piedpiper.h"

void PiedPiper::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
    if(str1=="roleAct") roleAct();
    else if(str1=="hasPuzzled") hasPuzzled(str2);
}

void PiedPiper::hasPuzzled(QString str){
    emit sendMessage(GAMEMESSAGE, str+QStringLiteral("号玩家已被迷惑"));
}

void PiedPiper::roleAct(){
    if(flag==0)
        emit sendMessage(GAMEMESSAGE, QStringLiteral("请选择两人迷惑"));
}
void PiedPiper::changeVoteStates(QString time, int delta){
    static int vote = 0;
    if(delta==0){
        vote=0;
    }else{
        vote+=delta;
    }
    if(time=="night"){
        if(vote==0){
            canVote(time,1);
            canCancelVote(time,0);
        }else if(vote==1){
            canVote(time,1);
            canCancelVote(time,1);
        }else{
            canVote(time,0);
            canCancelVote(time,1);
        }
    }else{
        if(vote==0){
            canVote(time,1);
            canCancelVote(time,0);
        }else{
            canVote(time,0);
            canCancelVote(time,1);
        }
    }
}
