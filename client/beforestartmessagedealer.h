/*************************************************
 * 名称： beforestartmessagedealer.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： BeforeStartMessageDealer类（MessageDealer派生类）。该类负责处理游戏开始前服务器和客户端UI发来的消息
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef BEFORESTARTMESSAGEDEALER_H
#define BEFORESTARTMESSAGEDEALER_H

#include "messagedealer.h"

class BeforeStartMessageDealer : public MessageDealer
{
    Q_OBJECT
public:
    using MessageDealer::MessageDealer;

public slots:
    void receiveMessage(QString str1,QString str2=0,QString str3=0,QString str4=0,QString str5=0);


};

#endif // BEFORESTARTMESSAGEDEALER_H
