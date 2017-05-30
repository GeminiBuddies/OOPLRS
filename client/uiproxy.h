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

    virtual bool setItem(QObject* item);
    virtual bool setItem(QString name);
    void setName(QString name);
    QString name;
    QObject* item;

    template<typename T>
    UiProxy* addChild(QString name,Messager* player);

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
