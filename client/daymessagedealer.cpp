#include "daymessagedealer.h"

DayMessageDealer::DayMessageDealer(Messager *player, MessageDealer *character):MessageDealer(player){
    this->character=character;
    for(int i=1;i<=20;i++){
        alive[i]=0;
    }
}

void DayMessageDealer::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5){
    qDebug("%s %s %s %s",qPrintable("realDayMessage"),qPrintable(str1),qPrintable(str2),qPrintable(str3));
    if(str1== "night")night();
    else if(str1== "alive") alive[QVariant(str2).toInt()]=1;
    else if(str1== "notAlive") alive[QVariant(str2).toInt()]=0;
    else if(str1== "chooseSheriff")chooseSheriff();
    else if(str1== "showSheriffCandidate")showSheriffCandidate(str2);
    else if(str1== "determineSheriff")determineSheriff(str2);
    else if(str1== "dead")showDied(str2);
    else if(str1== "showLastWords")showLastWords(str2,str3);
    else if(str1== "startChat")startChat(str2);
    else if(str1== "showChatMessage")showChatMessage(str2,str3);
    else if(str1== "startVote")startVote();
    else if(str1=="startDayVote") startDayVote();
    else if(str1== "showVote")showVote(str3,str2);//交换了一下顺序
    else if(str1== "showVoteResult")showVoteResult(str2,str3);
    else if(str1== "clicked")clicked(str2,str3);
    else if(str1=="showCharacter") showCharacter(str2,str3);
    else if(str1=="draw") draw();
    else if(str1=="startLastWords") startLastWords(str2);
    else if(str1=="canDetermine") emit sendMessage(GAMEMESSAGE, QStringLiteral("等待替罪羊选择下回合可以投票的人"));
    else if(str1=="exit") sheriffCandidateExit(str2);//选警长时退水
    else if(str1=="number") number=str2;
    else if(str1=="isSheriffCandidate") isSheriffCandidate=1;
    else if(str1=="changeSheriff") emit sendMessage(GAMEMESSAGE, QStringLiteral("请选择警徽给谁，如果不选则代表撕警徽"));
    else if(str1=="stopChat") stopChat();
    else if(str1=="playerNum"){
        for(int i=1;i<=QVariant(str2).toInt();i++){
            alive[i]=1;
        }
    }
}

void DayMessageDealer::night(){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("天黑了，大家睡觉吧~"));
    emit sendMessage("dealer", "night");
    emit sendMessage("changeTime","night");
    emit sendMessage("toServer","night");
    emit sendMessage("dealer", "showBigText", QStringLiteral("等待中"));
    emit sendMessage("dealer", "cancelChat");
    emit sendMessage("dealer", "clearClicked");
    voting = 0;
}


void DayMessageDealer::startDayVote(){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("开始公投"));
    voting = 1;
}

void DayMessageDealer::chooseSheriff(){
    emit sendMessage(GAMEMESSAGE, QStringLiteral("开始选警长啦~请选择是否竞选"));
    emit sendMessage("dealer", "chooseSheriff");
}

void DayMessageDealer::showSheriffCandidate(QString str){
    emit sendMessage(GAMEMESSAGE, str+QStringLiteral("号玩家竞选警长"));
    QString temp="characterImage"+str;
    emit sendMessage("dealer", temp, "mouseAreaEnabled");
    if(isSheriffCandidate)
        emit sendMessage("dealer", "showSheriffExitButton");
}

void DayMessageDealer::determineSheriff(QString str){
    if(str!="-1"){
        emit sendMessage(GAMEMESSAGE, str+QStringLiteral("号玩家当选警长"));
        emit sendMessage("dealer", "clearClicked");
        emit sendMessage("dealer", "hideSheriffExitButton");
    }else if(str=="-1")//撕警徽
        emit sendMessage(GAMEMESSAGE, QStringLiteral("警长撕掉了警徽"));
}

void DayMessageDealer::showDied(QString str){
    if(voting == 0)
        emit sendMessage(GAMEMESSAGE, str+QStringLiteral("号玩家于夜里死亡"));
    else
        emit sendMessage(GAMEMESSAGE, str+QStringLiteral("号玩家被公投死亡"));
    QString temp="characterImage"+str;
    emit sendMessage("dealer", temp, "changeImage","qrc:/images/images/died.png");
    emit sendMessage("dealer", temp, "cannotBeVoted");
    emit judge(str,"1");
}

void DayMessageDealer::showLastWords(QString str1, QString str2){
    QString temp=str1+QStringLiteral("号遗言：")+str2;
    emit sendMessage("dealer","showChatMessage",temp);

}

void DayMessageDealer::startChat(QString str1){
    emit sendMessage(GAMEMESSAGE, str1+QStringLiteral("号玩家开始发言"));
    //emit sendMessage("dealer", "canChat");
    emit judge(str1,"0");
}

void DayMessageDealer::showChatMessage(QString str1, QString str2){
    qDebug("%s", qPrintable("reallyShowChatMessage"));
    QString temp=str1+QStringLiteral("号：")+str2;
    emit sendMessage("dealer","showChatMessage", temp);
}

void DayMessageDealer::stopChat(){
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
        emit changeVoteStates("day",1);
        emit sendMessage("toServer","vote",temp2);
        emit sendMessage("dealer",str1,"finishClicked");
        emit sendMessage(GAMEMESSAGE, QStringLiteral("你选择了")+temp+QStringLiteral("号"));
        showVote(number,temp);

    }
    else if(str2=="0"&&canCancelVote==true){
        emit changeVoteStates("day",-1);
        emit sendMessage("toServer","cancelvote",temp2);
        emit sendMessage("dealer",str1,"finishClicked");
        emit sendMessage(GAMEMESSAGE, QStringLiteral("你取消选择了")+temp+QStringLiteral("号"));
        emit sendMessage("dealer", number, "hideVote");
    }
}

void DayMessageDealer::startVote(){
    for(int i=0;i<20;i++){
        if(alive[i]){
            QString temp="characterImage"+QVariant(i).toString();
            emit sendMessage("dealer", temp, "mouseAreaEnabled");
        }
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
    canVote=1;
    canCancelVote=0;
    emit changeVoteStates("day",0);
    emit sendMessage("clearClicked");
    temp="characterImage"+number;
    emit sendMessage("dealer", temp, "hideVote");
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
    emit judge(str,"2");
}

void DayMessageDealer::sheriffCandidateExit(QString str){
    emit sendMessage(GAMEMESSAGE, str+QStringLiteral("号玩家退水"));
    QString temp="characterImage"+str;
    emit sendMessage("dealer", temp, "mouseAreaDisabled");
}
