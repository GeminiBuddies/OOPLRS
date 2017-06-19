/*************************************************
 * 名称： option.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： Option类（UiProxy的派生类），负责接收由Player类传来的消息，控制UI中Option（设置界面）对象；接收UI中Option传来的消息，传给Player类
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef OPTIONPROXY_H
#define OPTIONPROXY_H

#include "uiproxy.h"

class OptionProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    QObject *checkbox1, *checkbox2, *checkbox3;
    QObject *slider1,*slider2,*slider3;
    QObject *nameInput;
    QObject *confirmButton;
};

#endif // OPTIONPROXY_H
