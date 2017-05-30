#include "timerproxy.h"

void TimerProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1=="timer"){
        startTimer(QVariant(str2).toInt());
    }
}

void TimerProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    timer=this->item->findChild<QObject*>("timer");
    text=this->item->findChild<QObject*>("text");
    attrs=this->item->findChild<QObject*>("attrs");
}

void TimerProxy::startTimer(int time){
    attrs->setProperty("counter",time);
    QMetaObject::invokeMethod(timer,"start");
}

