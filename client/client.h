
#ifndef CLIENT_H
#define CLIENT_H

#include "../cih/globalConf.h"
#include "messager.h"
#include <QObject>
#include <QSet>
#include <QString>
#include "clientconn.h"
#include "messager.h"

class Client : public Messager
{
	Q_OBJECT
	Messager* _player;
    ClientConn* _ClientConn = new ClientConn;
	Conn _server;
    QString _name;
    const QSet<Conn>* _ServerList;
	QString _ServerListname;
	QString _role;
	QString _message = "";
	QString _witch;
	bool _vote[200];
	bool _time = 0;
public:
	Client(Messager* player, QString name);
	void getServers();
	void sendVote();
public slots:
	void onClientData(byteseq data, int length);
    //void onClientDisconnect();
    void receiveMessage(QString str1, QString str2="", QString str3="", QString str4="", QString str5="");
};

#endif // CLIENTCONN_H
