/*************************************************
 * 名称： mainformproxy.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： MainFormProxy类（UiProxy的派生类），负责接收由Player类传来的消息，控制UI中的MainForm对象；接收UI中MainForm传来的消息，传给Player类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef MAINFORMPROXY_H
#define MAINFORMPROXY_H

#include "uiproxy.h"
#include "QPropertyAnimation"

class MainFormProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void nightAnimation();
    void dayAnimation();
    void roleActionStartAnimation();
    void roleActionEndAnimation();

private:
    QObject* weather=0;
    QObject* day=0;
    QObject* night=0;
    QObject* roleActionStart=0;
    QObject* roleActionEnd=0;
    QObject* bigText=0;
    void showBigText(QString str, QString str2="10000");
    void hideBigText();
};

#endif // MAINFORMPROXY_H
