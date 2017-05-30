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
    QObject* image=0;
    QObject* role=0;
    QObject* characterName=0;
    QObject* voteImage=0;
    QObject* voteText=0;

};

#endif // CHARACTERIMAGEPROXY_H
