 #include "player.h"

Player::Player(){
    character=NULL;
    BSMDealer=new BeforeStartMessageDealer(this);
    uiMessageDealer=new UiMessageDealer(this);
    QObject::connect(this, SIGNAL(sendMessageToBSMDealer(QString,QString,QString,QString,QString)), BSMDealer,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(this, SIGNAL(sendMessageToUiDealer(QString,QString,QString,QString,QString)),uiMessageDealer,SLOT(receiveMessage(QString,QString,QString,QString,QString)));

}

void Player::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    qDebug("%s %s %s %s", qPrintable("receive"), qPrintable( str1 ),qPrintable(str2), qPrintable(str3));
    if(str1=="dealer") emit sendMessage(str2,str3,str4,str5);
    else if(str1=="time") time=str2;
    else if(str1=="clicked") emit sendMessageToCharacter(str1,str2,str3,str4,str5);
    else if(str1=="toServer"){
        qDebug("%s %s %s %s %s", qPrintable("sendToServer"), qPrintable( str2 ),qPrintable(str3), qPrintable(str4), qPrintable(str5));
        emit sendMessageToServer(str2,str3,str4,str5);
    }
    else if(str1=="ui") emit sendMessageToUiDealer(str2,str3,str4,str5);
    else if(str1=="setPlayer") {
        initialClient(str2);
        name=str2;
        sex=str3;
    }
    else if(str1=="setTime") emit sendMessage("timer",str2);
    else if(str1=="server") serverToUi(str2,str3,str4);
    else
        serverToUi(str1,str2,str3);
}

void Player::getInfo(){
    emit sendMessageToServer(name,sex);
}

void Player::serverToUi(QString str1, QString str2, QString str3){
    qDebug("%s %s %s %s",qPrintable("send"),qPrintable(str1),qPrintable(str2),qPrintable(str3));
    if(time=="notInGame"){
        if(str1=="join") {
            playerNum++;
            emit sendMessageToBSMDealer(str1,str2,str3);
        }else if(str1=="getInfo") getInfo();
        else if(str1=="setImage"||str1=="info"){emit sendMessageToBSMDealer(str1,str2,str3);}
        else if(str1=="position") {this->number=str2;}
        else if(str1=="assignRoles") {
            emit sendMessageToBSMDealer(str1,str2,this->number);
            constructCharacter(str2);
            emit sendMessageToCharacter("playerNum", QVariant(playerNum).toString());
        }else if(str1=="serverList"){
            emit sendMessage(str1,str2);
        }else if(str1=="connectSucceed"){
            emit sendMessage("connectServerSucceed");
        }else if(str1=="disconn")
            emit sendMessage("sendGameMessage",QStringLiteral("你断线了~退了吧，并不能重连"));
    }
    else if(str1=="changeRole") changeRole(str2);
    else
        emit sendMessageToCharacter(str1,str2,str3);

}

void Player::changeRole(QString str2){
    QString temp="characterImage"+this->number;
    emit sendMessage(temp, "changeRole", "qrc:/images/images/"+str2+".jpg");
    constructCharacter(str2);
    emit sendMessageToCharacter("playerNum",QVariant(playerNum).toString());
    emit sendMessageToCharacter("changeTime",time);
}

void Player::initialClient(QString str){
    client=new Client(this,str);
    QObject::connect(this,SIGNAL(sendMessageToServer(QString,QString,QString,QString,QString)),client,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(client,SIGNAL(sendMessage(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
}

void Player::constructCharacter(QString role){
    emit sendMessageToServer("assignRoles",role);
    if(character!=NULL)
        delete character;
    if(role=="werewolf")
        character=new Werewolf(this,number);
    else if(role=="ancient")
        character=new Ancient(this,number);
    else if (role == "cupid")
        character=new Cupid(this,number);
    else if (role == "hunter")
        character=new Hunter(this,number);
    else if (role == "idiot")
        character=new Idiot(this,number);
    else if (role == "savior")
        character=new Savior(this,number);
    else if (role == "scapegoat")
        character=new Scapegoat(this,number);
    else if (role == "seer")
        character=new Seer(this,number);
    else if (role == "townsfolk")
        character=new Townsfolk(this,number);
    else if (role == "witch")
        character=new Witch(this,number);
    else if(role == "thief")
        character=new Thief(this,number);
    else if(role == "dead")
        character = new Dead(this,number);
    QObject::connect(this,SIGNAL(sendMessageToCharacter(QString,QString,QString,QString,QString)),character,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
    QObject::connect(character,SIGNAL(sendMessageToPlayer(QString,QString,QString,QString,QString)),this,SLOT(receiveMessage(QString,QString,QString,QString,QString)));
}
