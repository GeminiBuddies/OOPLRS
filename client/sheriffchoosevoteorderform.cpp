#include "sheriffchoosevoteorderform.h"
void SheriffChooseVoteOrderFormProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(item,SIGNAL(sheriffChoose(int)),this,SLOT(sheriffChoose(int)));
}

void SheriffChooseVoteOrderFormProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1=="chooseSheriffVoteOrder"){
        this->item->setProperty("visible",QVariant(true));
    }
}

void SheriffChooseVoteOrderFormProxy::sheriffChoose(int i){
    if(i==1) {
        sendMessage("toServer","positive");
    }
    else if(i==2) sendMessage("toServer","negative");
}
