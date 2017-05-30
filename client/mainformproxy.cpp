#include "mainformproxy.h"

void MainFormProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
}

void MainFormProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1==QString("day"))
        dayAnimation();
    else if(str1==QString("night"))
        nightAnimation();
    else if(str1==QString("roleActionStart"))
        roleActionStartAnimation();
    else if(str1==QString("roleActionEnd"))
        roleActionEndAnimation();

}

void MainFormProxy::dayAnimation(){
    if(weather==NULL)
        weather=item->findChild<QObject*>("weather");
    if(day==NULL)
        day=weather->findChild<QObject*>("day");
    day->setProperty("running",QVariant(true));

}

void MainFormProxy::nightAnimation(){
    if(weather==NULL)
        weather=item->findChild<QObject*>("weather");
    if(night==NULL)
        night=weather->findChild<QObject*>("night");
    night->setProperty("running",QVariant(true));
}

void MainFormProxy::roleActionStartAnimation(){
    if(weather==NULL)
        weather=item->findChild<QObject*>("weather");
    if(roleActionStart==NULL)
        roleActionStart=weather->findChild<QObject*>("roleActionStart");
    roleActionStart->setProperty("running",QVariant(true));
}

void MainFormProxy::roleActionEndAnimation(){
    if(weather==NULL)
        weather=item->findChild<QObject*>("weather");
    if(roleActionEnd==NULL)
        roleActionEnd=weather->findChild<QObject*>("roleActionEnd");
    roleActionEnd->setProperty("running",QVariant(true));
}
