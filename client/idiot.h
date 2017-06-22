/*************************************************
 * 名称： idiot.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： Idiot类（Character派生类），负责处理角色“白痴”的特殊消息
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef IDIOT_H
#define IDIOT_H


#include "character.h"
class Idiot : public Character
{
    Q_OBJECT
public:
    using Character::Character;
    void judge(QString str1, QString str2);

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");


private:


};

#endif // IDIOT_H
