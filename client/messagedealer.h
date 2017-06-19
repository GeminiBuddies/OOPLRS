/*************************************************
 * 名称： messagedealer.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： MessageDealer抽象类（Messager的派生类），为所有消息处理类的子类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef MESSAGEDEALER_H
#define MESSAGEDEALER_H

#include "messager.h"
#include "uiproxy.h"

class MessageDealer : public Messager
{
    Q_OBJECT
public:
    MessageDealer(Messager* player);

protected:
    Messager* player;

signals:

};

#endif // MESSAGEDEALER_H
