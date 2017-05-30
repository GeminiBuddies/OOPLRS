#include "thiefchooseformproxy.h"

void ThiefChooseFormProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(item,SIGNAL(thiefChoose(int)),this,SLOT(thiefChoose(int)));
}

void ThiefChooseFormProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1=="thiefAct"){
        this->item->setProperty("visible",QVariant(true));
        QObject* temp=this->item->findChild<QObject*>("rowLayout");
        image1=temp->findChild<QObject*>("image1");
        image2=temp->findChild<QObject*>("image2");
        image1->setProperty("source","qrc:/images/images/"+str2+".jpg");
        image2->setProperty("source","qrc:/images/images/"+str3+".jpg");
    }
}

void ThiefChooseFormProxy::thiefChoose(int i){
    if(i==0) sendMessage("toServer","thiefChoose","0");
    else if(i==1) sendMessage("toServer","thiefChoose","1");
    else if(i==2) sendMessage("toServer","thiefChoose","2");
}
