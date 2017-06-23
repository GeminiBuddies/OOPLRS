/*************************************************
 * 名称： uiproxy.h
 * 作者： 赵欣昊
 * 时间： 20170616
 * 内容描述： UiProxy类（Messager派生类），为客户端程序中所有UI代理类的基类，
 *      在Messager类的基础上，拥有多个信号槽，功能见代码
 *      所有UiProxy构成一棵树
 * 版权： 这是我们自行完成的程序，没有使用其他来源代码
 ************************************************/

#ifndef UIPROXY_H
#define UIPROXY_H

#include "messager.h"
#include <QMap>
#include <QString>

class UiProxy : public Messager
{
    Q_OBJECT
public:

    explicit UiProxy(UiProxy* parent=0, Messager* player=0);
    virtual ~UiProxy();

    virtual bool setItem(QObject* item);//以某个QObject指针为参数设置UiProxy类的item
    virtual bool setItem(QString name);//以QObject的objectName为参数设置UiProxy类的item
    void setName(QString name);//设置该Proxy类的名字
    QString name;
    QObject* item;//被代理的对象

    template<typename T>
    UiProxy* addChild(QString name,Messager* player);//添加子UiProxy

    QMap<QString, UiProxy*> children;

    virtual void connectSignal();

signals:


public slots:
    virtual void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "") = 0;

protected:
    UiProxy* parent;
    Messager* player;


};

template<typename T>
UiProxy* UiProxy::addChild(QString name, Messager* player){
    children[name]=new T(this,player);
    children[name]->name=name;
    return children[name];
}


#endif // UIPROXY_H
