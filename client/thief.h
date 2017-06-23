/*************************************************
 * 名称： thief.h
 * 作者： 赵欣昊
 * 时间： 20170623
 * 内容描述： Thief类（Character派生类），负责处理角色“盗贼”的特殊消息
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef THIEF_H
#define THIEF_H

#include "character.h"
class Thief : public Character
{
    Q_OBJECT
public:
    using Character::Character;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

};

#endif // THIEF_H
