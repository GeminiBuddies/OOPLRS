/*************************************************
 * 名称： gamerecorderproxy.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： GameRecorderProxy类（UiProxy的派生类），负责接收由Player类传来的消息，控制UI中的GameRecorder对象；接收UI中GameRecorder传来的消息，传给Player类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef GAMERECORDERPROXY_H
#define GAMERECORDERPROXY_H

#include "uiproxy.h"

class GameRecorderProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:
    void sendGameMessage(QVariant str);

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");


};

#endif // GAMERECORDERPROXY_H
