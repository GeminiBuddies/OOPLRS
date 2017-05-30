#include "uimessagedealer.h"

void UiMessageDealer::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    QString temp="";
    temp+=char(QVariant(str2).toInt()+'a');
    if(str1=="vote") sendMessage("toServer",str1,temp);
    else if(str1=="cancelVote") sendMessage("toServer",str1,temp);
    else if(str1=="connectServer") sendMessage("toServer",str1,str2);
    else if(str1=="getServer") sendMessage("toServer",str1);
}
