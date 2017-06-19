/*************************************************
 * 名称： seer.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： Seer类（Character派生类），负责处理角色“预言家”的特殊消息
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef SEER_H
#define SEER_H

#include "character.h"
class Seer : public Character
{
    Q_OBJECT
public:
    using Character::Character;

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    void showIdentity(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");
    void roleAct(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

};

#endif // SEER_H
