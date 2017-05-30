#include "mainwindowproxy.h"

void MainWindowProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
}

void MainWindowProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){

}
