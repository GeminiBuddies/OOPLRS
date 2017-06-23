/*************************************************
 * 名称： timerproxy.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： TimerProxy类（UiProxy的派生类），负责接收由Player类传来的消息，控制UI中Timer（计时器）对象；接收UI中Timer传来的消息，传给Player类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef TIMERPROXY_H
#define TIMERPROXY_H

#include "uiproxy.h"

class TimerProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    QObject* timer;
    QObject* text;
    QObject* attrs;
    void startTimer(int time);
};


#endif // TIMERPROXY_H
