#include "temp.h"

void Temp::sendChatMessage(QString str){
    QChar* Iterator=str.data();
        QString strr[3];
        for(int i=0;i<3;i++){
            while(*Iterator!=' '&&!Iterator->isNull()){
                strr[i].append(*Iterator);
                Iterator++;
            }
            Iterator++;
        }
        emit sendMessage(strr[0],strr[1],strr[2]);

}

void Temp::connectSignal(){
    QObject::connect(this->item,SIGNAL(sendMessage(QString)),this,SLOT(sendChatMessage(QString)));
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    sendBox=this->item->findChild<QObject*>("sendBox");
}

void Temp::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){

}
