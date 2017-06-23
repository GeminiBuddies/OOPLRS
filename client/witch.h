/*************************************************
 * 名称： witch.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： Witch类（Character派生类），负责处理角色“女巫”的特殊消息
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef WITCH_H
#define WITCH_H

#include "character.h"
class Witch : public Character
{
    Q_OBJECT
public:
    using Character::Character;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    void roleAct(QString str1,QString str2);
};

#endif // WITCH_H
