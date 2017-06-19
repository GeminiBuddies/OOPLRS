/*************************************************
 * 名称： mousearea.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： MouseArea类（UiProxy的派生类），负责接收由Player类传来的消息，控制UI中CharacterImage中的MouseArea对象；接收UI中MouseArea传来的消息，传给Player类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef MOUSEAREA_H
#define MOUSEAREA_H

#include "uiproxy.h"
#include <QVariant>

class MouseArea : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void mouseAreaEnabled(bool enabled);
    void connectSignal();

public slots:
    void onClicked();
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    bool isClicked=0;
    bool canBeVoted=0;
};

#endif // MOUSEAREA_H
