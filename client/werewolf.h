/*************************************************
 * 名称： werewolf.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： Werewolf类（Character派生类），负责处理角色“狼人”的特殊消息
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef WEREWOLF_H
#define WEREWOLF_H

#include "character.h"
class Werewolf : public Character
{
    Q_OBJECT
public:
    using Character::Character;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

};

#endif // WEREWOLF_H
