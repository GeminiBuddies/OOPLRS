#include "welcomeformproxy.h"

void WelcomeFormProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(this->item,SIGNAL(setPlayer(QString, bool)),this,SLOT(getPlayerSetting(QString,bool)));
}

void WelcomeFormProxy::getPlayerSetting(QString name, bool sex){
    if(sex) sendMessage("setPlayer", name, "male");
    else sendMessage("setPlayer",name, "female");
}

void WelcomeFormProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){

}
