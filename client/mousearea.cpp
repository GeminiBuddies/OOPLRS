#include "mousearea.h"

void MouseArea::mouseAreaEnabled(bool enabled){
    item->setProperty("enabled",QVariant(enabled));
}

void MouseArea::onClicked(){
    QString temp;
    if(!isClicked==1)
        temp="1";
    else
        temp="0";
    sendMessage("clicked",parent->name, temp);
}

void MouseArea::connectSignal(){
    QObject::connect(this->item,SIGNAL(mouseAreaClicked()),this,SLOT(onClicked()));
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));

}

void MouseArea::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1==parent->name){
        if(str2=="canBeVoted") canBeVoted=1;
        else if(str2=="cannotBeVoted") {
            canBeVoted=0;
            mouseAreaEnabled(0);
        }
        else if(str2=="finishClicked"){
            isClicked=!isClicked;
        }
        else if(canBeVoted){
            if(str2=="mouseAreaEnabled")
                mouseAreaEnabled(1);
            else if(str2=="mouseAreaDisabled"){
                mouseAreaEnabled(0);
                isClicked=0;
            }
        }
    }
    else if(str1=="clearClicked"){
        isClicked=0;
    }
}
