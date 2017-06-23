/*************************************************
 * 名称： uimessagedealer.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： UiMessageDealer类（MessageDealer派生类）。该类负责处理游戏开始后部分与时间无关的客户端UI发来的消息
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef UIMESSAGEDEALER_H
#define UIMESSAGEDEALER_H

#include "messagedealer.h"

class UiMessageDealer : public MessageDealer
{
    Q_OBJECT
public:
    using MessageDealer::MessageDealer;

public slots:
    void receiveMessage(QString str1,QString str2=0,QString str3=0,QString str4=0,QString str5=0);


};

#endif // UIMESSAGEDEALER_H
