/*************************************************
 * 名称： witchchooseformproxy.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： WitchChooseFormProxy类（UiProxy类的子类），负责接收由Player类传来的消息，控制UI中的WitchChooseForm对象；接收UI中WitchChooseForm传来的消息，传给Player类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef WITCHCHOOSEFORMPROXY_H
#define WITCHCHOOSEFORMPROXY_H

#include "uiproxy.h"

class WitchChooseFormProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:
    void witchAct();

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void witchChoose(int i);

private:
    QObject* button1;
    QObject* button2;

};

#endif // WITCHCHOOSEFORMPROXY_H
