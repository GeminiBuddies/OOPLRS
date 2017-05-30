#include "cupid.h"

void Cupid::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
    if(str1=="roleAct"){
        emit sendMessage(GAMEMESSAGE, QStringLiteral("请选择两个人结为情侣"));
    }
}

void Cupid::changeVoteStates(QString time, int delta){
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
