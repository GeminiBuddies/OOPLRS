/*************************************************
 * 名称： temp.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： 测试类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef TEMP_H
#define TEMP_H


#include"uiproxy.h"

class Temp : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

public slots:
    void sendChatMessage(QString str);
    void receiveMessage(QString str1,QString str2,QString str3,QString str4,QString str5);

private:
    QObject* sendBox;

};

#endif // TEMP_H
