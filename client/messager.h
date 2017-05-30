#ifndef MESSAGER_H
#define MESSAGER_H

#include <QObject>
#include <QVariant>
#define GAMEMESSAGE "dealer","sendGameMessage"

class Messager : public QObject
{
    Q_OBJECT
public:


signals:
    void sendMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

public slots:
    virtual void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "") = 0;
};

#endif // MESSAGER_H
