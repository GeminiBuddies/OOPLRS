#ifndef ENDLISTPROXY_H
#define ENDLISTPROXY_H


#include "uiproxy.h"
#include <QVector>

class EndListProxy : public UiProxy
{
    Q_OBJECT
public:
    using UiProxy::UiProxy;
    void connectSignal();

signals:

public slots:
    void receiveMessage(QString str1, QString str2 = "", QString str3 = "", QString str4 = "", QString str5 = "");

private:
    QObject* confirmButton;
    QObject* refreshButton;
    QVector<QString> serverList;
    void setEndList(QString str1, QString str2);
    void showEndList();
};

#endif // ENDLISTPROXY_H
