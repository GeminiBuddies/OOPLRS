#include "gamerecorderproxy.h"

void GameRecorderProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(this,SIGNAL(sendGameMessage(QVariant)),this->item,SLOT(showMessage(QVariant)));
}


void GameRecorderProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1=="sendGameMessage")
        emit sendGameMessage(QVariant(str2));
}
