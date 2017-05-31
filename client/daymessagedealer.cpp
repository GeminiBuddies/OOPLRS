#include "daymessagedealer.h"

DayMessageDealer::DayMessageDealer(Messager *player, MessageDealer *character):MessageDealer(player){
    this->character=character;
}

void DayMessageDealer::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    if(str1== "night")night();
    else if(str1== "chooseSheriff")chooseSheriff();
    else if(str1== "showSheriffCandidate")showSheriffCandidate(str2);
    else if(str1== "determineSheriff")determineSheriff(str2);
    else if(str1== "dead")showDied(str2);
    else if(str1== "showLastWords")showLastWords(str2,str3);
    else if(str1== "startChat")startChat(str2);
    else if(str1== "showChatMessage")showChatMessage(str2,str3);
    else if(str1== "vote")startVote();
    else if(str1== "showVote")showVote(str3,str2);//交换了一下顺序
    else if(str1== "showVoteResult")showVoteResult(str3,str2);//交换了一下顺序
    else if(str1== "win")win();
    else if(str1== "lose")lose();
    else if(str1== "clicked")clicked(str2,str3);
    else if(str1=="showCharacter") showCharacter(str2,str3);
    else if(str1=="draw") draw();
    else if(str1=="startLastWords") startLastWords(str2);
}

void DayMessageDealer::night(){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("天黑了，大家睡觉吧~"));
    emit sendMessage("dealer", "night");
    emit sendMessage("changeTime","night");
    emit sendMessage("toServer","night");
    emit sendMessage("dealer", "showBigText", QStringLiteral("等待中"));
    emit sendMessage("dealer", "cancelChat");
}

void DayMessageDealer::chooseSheriff(){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("开始选警长啦~请选择是否竞选"));
}

void DayMessageDealer::showSheriffCandidate(QString str){
    emit sendMessage(GAMEMESSAGE, str+QStringLiteral("号玩家竞选警长"));
    QString temp="characterImage"+str;
    emit sendMessage("dealer", temp, "mouseAreaEnabled");
}

void DayMessageDealer::determineSheriff(QString str){
    emit sendMessage(GAMEMESSAGE, str+QStringLiteral("号玩家当选警长"));
}

void DayMessageDealer::showDied(QString str){
    emit sendMessage(GAMEMESSAGE, str+QStringLiteral("号玩家于夜里死亡"));
    QString temp="characterImage"+str;
    emit sendMessage("dealer", temp, "changeImage","qrc:/images/images/died.png");
    emit sendMessage("dealer", temp, "cannotBeVoted");
    emit judge(str, "0");
}

void DayMessageDealer::showLastWords(QString str1, QString str2){
    QString temp=str1+QStringLiteral("号遗言：")+str2;
    emit sendMessage("dealer","showChatMessage",temp);
    emit sendMessage("dealer", "cancelChat");
    emit sendMessage("dealer", "hideBigText");
}

void DayMessageDealer::startChat(QString str1){
    emit sendMessage(GAMEMESSAGE, str1+QStringLiteral("号玩家开始发言"));
    emit sendMessage("dealer", "canChat");
    judge(str1,"0");
}

void DayMessageDealer::showChatMessage(QString str1, QString str2){
    QString temp=str1+QStringLiteral("号：")+str2;
    emit sendMessage("dealer","showChatMessage", temp);
    emit sendMessage("dealer", "cancelChat");
    emit sendMessage("dealer", "hideBigText");
}

void DayMessageDealer::win(){
    emit sendMessage("changeTime","notInGame");
    emit sendMessage(GAMEMESSAGE, QStringLiteral("你赢了！"));
}

void DayMessageDealer::lose(){
    emit sendMessage("changeTime","notInGame");
    emit sendMessage(GAMEMESSAGE, QStringLiteral("你输了！"));
}

void DayMessageDealer::clicked(QString str1, QString str2){
    QString temp="";
    int x;
    char t;
    if(str1.length()==15){
        temp+=str1[14];
        x=QVariant(temp).toInt();
        t='a'+x;
    }

    else if(str1.length()==16){
        temp+=str1[14];
        temp+=str1[15];
        x=QVariant(temp).toInt();
        t='a'+x;
    }
    QString temp2="";
    temp2+=t;
    if(str2=="1"&&canVote==true){
        changeVoteStates("day",1);
        emit sendMessage("toServer","vote",temp2);
        emit sendMessage("dealer",str1,"finishClicked");
        emit sendMessage(GAMEMESSAGE, QStringLiteral("你选择了")+temp+QStringLiteral("号"));
    }
    else if(str2=="0"&&canCancelVote==true){
        changeVoteStates("day",-1);
        emit sendMessage("toServer","cancelvote",temp2);
        emit sendMessage("dealer",str1,"finishClicked");
        emit sendMessage(GAMEMESSAGE, QStringLiteral("你取消了选择"));
    }
}

void DayMessageDealer::startVote(){
    for(int i=0;i<20;i++){
        QString temp="characterImage"+QVariant(i).toString();
        emit sendMessage("dealer", temp, "mouseAreaEnabled");
    }
}

void DayMessageDealer::showVote(QString str1, QString str2){
    QString temp="characterImage"+str1;
    emit sendMessage("dealer", temp, "showVote", str2);
}

void DayMessageDealer::showVoteResult(QString str1,QString str2){
    emit sendMessage(GAMEMESSAGE, str1+QStringLiteral("号玩家投给了")+str2+QStringLiteral("号玩家"));
    QString temp="characterImage"+str1;
    emit sendMessage("dealer", temp, "hideVote");
    for(int i=0;i<20;i++){
        QString temp="characterImage"+QVariant(i).toString();
        emit sendMessage("dealer",temp,"mouseAreaDisabled");
    }
}

void DayMessageDealer::showCharacter(QString str1, QString str2){
    emit sendMessage(GAMEMESSAGE, str1+QStringLiteral("号玩家死亡，该玩家是")+str2);
    QString temp="characterImage"+str1;
    emit sendMessage("dealer",temp,"changeRole", "qrc:/images/images/"+str2+".jpg");
}

void DayMessageDealer::draw(){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("平票"));
}

void DayMessageDealer::startLastWords(QString str){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("请")+str+QStringLiteral("号玩家发表遗言"));
    judge(str,"1");
}
