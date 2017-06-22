#include "idiot.h"

void Idiot::receiveMessage(QString str1, QString str2 , QString str3, QString str4 , QString str5 ){
    Character::receiveMessage(str1,str2,str3,str4,str5);
}

void Idiot::judge(QString str1, QString str2){
    //str2为0代表发言，str2为1代表死人了
    if(str2=="1"){
        alive[QVariant(str1).toInt()]=0;
        emit sendMessageToDMDealer("notAlive", str1);
        emit sendMessageToNMDealer("notAlive", str1);
    }
    if(str1==number)
        if(str2=="1"){
            emit sendMessage(GAMEMESSAGE,QStringLiteral("你死了"));
            emit sendMessage(GAMEMESSAGE, QStringLiteral("请发表遗言"));
            emit sendMessage("dealer", "showBigText", QStringLiteral("请发表遗言"));
            emit sendMessage("dealer", "canChat");
        }else if(str2=="0"){
            emit sendMessage("dealer", "canChat");
            emit sendMessage(GAMEMESSAGE, QStringLiteral("请发言"));
            emit sendMessage("dealer", "showBigText", QStringLiteral("请发言"));
        }
}
