#include "endlistproxy.h"

void EndListProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1=="setEndList"){
        setEndList(str2,str3);
    }else if(str1=="showEndList"){
        showEndList();
    }
}

void EndListProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
}

void EndListProxy::showEndList(){
    this->item->setProperty("visible",QVariant(true));
}

void EndListProxy::setEndList(QString str1, QString str2){
    QMetaObject::invokeMethod(this->item,"addElement",Q_ARG(QVariant,QVariant(str1)),Q_ARG(QVariant, QVariant(str2)));
}
