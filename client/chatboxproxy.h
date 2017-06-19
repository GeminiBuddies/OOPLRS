/*************************************************
 * 名称： chatboxproxy.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： ChatBoxProxy类（UiProxy的派生类），负责接收由Player类传来的消息，控制UI中的ChatBox对象；接收UI中ChatBox传来的消息，传给Player类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef CHATBOXPROXY_H
#define CHATBOXPROXY_H

#include"uiproxy.h"

class ChatBoxProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();
    void showChatMessage(QString str);

public slots:
    void sendChatMessage(QString str);
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    QObject* sendBox;
    void canChat();
    void cancelChat();
    bool chat=1;

};

#endif // CHATBOXPROXY_H
