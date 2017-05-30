#include "optionproxy.h"

void OptionProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){

}

void OptionProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject* temp=this->item->findChild<QObject*>("gridLayout");
    checkbox1=temp->findChild<QObject*>("checkBox1");
    checkbox2=temp->findChild<QObject*>("checkBox2");
    checkbox3=temp->findChild<QObject*>("checkBox3");
    slider1=temp->findChild<QObject*>("slider1");
    slider2=temp->findChild<QObject*>("slider2");
    slider3=temp->findChild<QObject*>("slider3");
    nameInput=temp->findChild<QObject*>("nameInput");
    temp=this->item->findChild<QObject*>("rowLayout");
    QObject* temp2=temp->findChild<QObject*>("confirm");
    confirmButton=temp2->findChild<QObject*>("mouseArea");

}
