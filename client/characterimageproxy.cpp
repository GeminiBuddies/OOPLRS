#include "characterimageproxy.h"

void CharacterImageProxy::connectSignal(){
    QObject::connect(this,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(player,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
}

void CharacterImageProxy::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1==this->name){
        if(str2=="changeImage") changeImage(str3);
        else if(str2=="changeRole") changeRole(str3);
        else if(str2=="changeName") changeName(str3);
        else if(str2=="showVote") showVote(str3);
        else if(str2=="hideVote") hideVote();
    }
}

void CharacterImageProxy::changeImage(QString url){
    if(image==NULL)
        image=this->item->findChild<QObject*>("characterImage");
    image->setProperty("source",QVariant(url));
}

void CharacterImageProxy::changeRole(QString url){
    if(role==NULL)
        role=this->item->findChild<QObject*>("role");
    role->setProperty("source",QVariant(url));
}

void CharacterImageProxy::changeName(QString name){
    if(characterName==NULL)
        characterName=this->item->findChild<QObject*>("characterName");
    characterName->setProperty("text",name);
}

void CharacterImageProxy::showVote(QString str){
    if(voteImage==NULL)
        voteImage=this->item->findChild<QObject*>("voteImage");
    if(voteText==NULL)
        voteText=voteImage->findChild<QObject*>("voteText");
    voteImage->setProperty("visible",QVariant(true));
    voteText->setProperty("text",QVariant(str));
}

void CharacterImageProxy::hideVote(){
    if(voteImage==NULL)
        voteImage=this->item->findChild<QObject*>("voteImage");
    voteImage->setProperty("visible", QVariant(false));
}
