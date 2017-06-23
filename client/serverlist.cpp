#include "serverlistproxy.h"

void ServerListProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1=="serverList"){
        setServerList(str2);
    }else if(str1=="connectServerSucceed"){
        connectServerSucceed();
    }
}

void ServerListProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    confirmButton=this->item->findChild<QObject*>("confirm");
    QObject::connect(confirmButton,SIGNAL(connectServer(int)),this,SLOT(connectServer(int)));
    refreshButton=this->item->findChild<QObject*>("refresh");
    QObject::connect(refreshButton,SIGNAL(getServer()),this,SLOT(getServer()));
    //TEMP
    //connectServerSucceed();
}

void ServerListProxy::connectServerSucceed(){
    QObject* mainWindow=this->parent->item;
    mainWindow->setProperty("width",QVariant(1280));
    mainWindow->setProperty("height",QVariant(800));
    this->parent->children["mainFormProxy"]->item->setProperty("visible",QVariant(true));
    this->item->setProperty("visible",QVariant(false));
}

void ServerListProxy::connectServer(int index){
    emit sendMessage("ui","connectServer",serverList[index]);
}

void ServerListProxy::getServer(){
    emit sendMessage("ui", "getServer");
}

void ServerListProxy::setServerList(QString str){
    QMetaObject::invokeMethod(this->item,"clear");
    serverList.clear();
    QString temp = "";
    if(str!=""){
        for(int i=0;i<str.length();i++){
            if(str[i]!=QChar('-'))
                temp+=str[i];
            else{
                serverList.append(temp);
                temp="";
            }
        }
        serverList.append(temp);
        confirmButton->setProperty("visible",true);//把按钮显示
        QMetaObject::invokeMethod(this->item,"clear");
        for(int i=0;i<serverList.length();i++){
            QMetaObject::invokeMethod(this->item,"addElement",Q_ARG(QVariant,QVariant(i+1)),Q_ARG(QVariant, QVariant(serverList[i])));
        }
    }
    else
        confirmButton->setProperty("visible",false);//把按钮隐藏
}

