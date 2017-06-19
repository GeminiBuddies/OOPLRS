/*************************************************
 * 名称： messagedealer.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： Messager类（QObject派生类），为客户端程序中几乎所有类的基类，拥有一个槽和一个信号，完成各个类之间的消息传输功能
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

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
