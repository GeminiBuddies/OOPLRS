#include "witchchooseformproxy.h"

void WitchChooseFormProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(this->item,SIGNAL(witchChoose(int)),this,SLOT(witchChoose(int)));
    button1=item->findChild<QObject*>("button1");
    button2=item->findChild<QObject*>("button2");
}

void WitchChooseFormProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1=="witchAct"){
        this->item->setProperty("visible",QVariant(true));
    if(str2=="0")
        button1->setProperty("visible",QVariant(false));
    else
        button1->setProperty("visible",QVariant(true));
    if(str3=="0")
        button2->setProperty("visible",QVariant(false));
    else
        button2->setProperty("visible",QVariant(true));

    }
}

void WitchChooseFormProxy::witchChoose(int i){
    emit sendMessage("toServer", "voteByWitch", QVariant(i).toString());
    if(i==0)
        emit sendMessage(GAMEMESSAGE,QStringLiteral("你选择不使用"));
    else if(i==1)
        emit sendMessage(GAMEMESSAGE,QStringLiteral("你选择使用毒药"));
    else if(i==2)
        emit sendMessage(GAMEMESSAGE,QStringLiteral("你选择使用解药"));
}
