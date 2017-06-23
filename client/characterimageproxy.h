/*************************************************
 * 名称： characterimageproxy.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： CharacterImageProxy类（UiProxy的派生类），负责接收由Player类传来的消息，控制UI中的CharacterImage对象；接收UI中CharacterImage传来的消息，传给Player类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef CHARACTERIMAGEPROXY_H
#define CHARACTERIMAGEPROXY_H

#include "uiproxy.h"

class CharacterImageProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();


signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    void changeImage(QString url);
    void changeRole(QString url);
    void changeName(QString name);
    void showVote(QString str);
    void hideVote();
    void showNumber(QString str);
    void setSheriff(QString str);
    void puzzled();
    void thisIsYou();
    QObject* image=0;
    QObject* role=0;
    QObject* characterName=0;
    QObject* voteImage=0;
    QObject* voteText=0;

};

#endif // CHARACTERIMAGEPROXY_H
