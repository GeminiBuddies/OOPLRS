#include "uiproxy.h"

UiProxy::UiProxy(UiProxy* parent,Messager* player){
    this->parent=parent;
    this->player=player;
}

UiProxy::~UiProxy(){
    if(player!=NULL)
        delete player;
}

bool UiProxy::setItem(QString name){
    return item=parent->item->findChild<QObject*>(name);
}

bool UiProxy::setItem(QObject* item){
    return this->item=item;
}

void UiProxy::setName(QString name){
   this->name=name;
}

void UiProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
}
