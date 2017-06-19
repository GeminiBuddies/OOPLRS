#include "messager.h"
#include <QObject>
#include <QSet>
#include <QString>
#include <cstring>
#include "client.h"

Client::Client(Messager* player, QString name)
{
	_player = player;
    QObject::connect(_ClientConn, SIGNAL(onServerData(byteseq,int)), this, SLOT(onClientData(byteseq,int)));
    //QObject::connect(_ClientConn, SIGNAL(onServerDisconnect), this, SLOT(onClientDisconnect));
	_name = name;
	_ClientConn -> start(_name);
	getServers();
}
void Client::getServers()
{
	_ServerList = _ClientConn -> getServers();
	_ServerListname = "";
    for (QSet<Conn>::const_iterator it = _ServerList -> begin(); it != _ServerList -> end(); ++it)
    {
		if(it != _ServerList -> end() - 1)
        _ServerListname = _ServerListname + GetName(*it) + "-";
		else 
        _ServerListname = _ServerListname + GetName(*it);
	}
    emit sendMessage("server", "serverList", _ServerListname);
}
void Client::onClientData(byteseq data, int length)
{
	int pos[2];
	pos[0] = 0;
	pos[1] = 0;
	int n = -1;
    QString str1 = "";
    QString str3 = "";
    QString str2 = "";
	for (int i = 0; i < length; ++i)
    {
		if(data[i] == '/')
		{
			n++;
			pos[n] = i;
		}
	}
	if (n == -1)
	{
        for(int i=0;i<length;i++){
            str1+=data[i];
        }
	}
	else if (n == 0)
	{
        /*char* char1=new char[pos[0]];
        char* char2=new char[length-1-pos[0]];*/
		for (int i = 0; i < pos[0]; ++i)
		{
            str1+=data[i];
		}
		for (int i = pos[0]+1; i < length; ++i)
		{
            str2+=data[i];
        }
        /*str1 = QString(char1);
        str2 = QString(char2);*/

	}
    else if (n == 1)
	{
        /*char *char1=new char[pos[0]];
        char *char2=new char[pos[1]-1-pos[0]];
        char *char3=new char[length-1-pos[1]];*/
		for (int i = 0; i < pos[0]; ++i)
		{
            str1+=data[i];
		}
		for (int i = pos[0]+1; i < pos[1]; ++i)
		{
            str2+=data[i];
		}
		for (int i = pos[1]+1; i < length; ++i)
		{
            str3+=data[i];
        }
	}
	if (str1 == "roleActEnd")
	{
        emit sendMessage(str1,str2,str3);
        if (_role == "witch" && _time == 1)
		{
			for (int i = 0; i < 200; ++i)
			{
				if (_witch == "0")
				{
					QString vote = "vote/0";
					QByteArray data0 = vote.toLatin1();
					char* data = data0.data();
                    int length = int(strlen(data));
                    _ClientConn->sendData(data, length);
				}
				else if (_vote[i] == 1)
				{
					char num = char(i);
					QString strnum = QString(num);
					QString vote = "vote/" + _witch +"/"+ strnum;
					QByteArray data0 = vote.toLatin1();
					char* data = data0.data();
                    int length = int(strlen(data));
                    _ClientConn->sendData(data, length);
				}
			}
		}
		else
			sendVote();
		for (int i = 0; i < 200; ++i)
		{
			_vote[i] = 0;
		}
	}
    else if (str1 == "roleAct" && _time == 0)
	{
		
	}
    else if (str1 == "showVoteResult" && _role != "werewolf" && _time == 1)
	{
		
	}
    else if (str1 == "getMessage")
	{
		QByteArray data0 = _message.toLatin1();
		char* data = data0.data();
        int length = int(strlen(data));
        _ClientConn->sendData(data, length);
		_message = "";
	}
    else
        emit sendMessage(str1,str2,str3);
}
/*
void Client::onClientDisconnect()
{

}
*/
void Client::sendVote()
{
	for (int i = 0; i < 200; ++i)
	{
		if (_vote[i] == 1)
		{
			char num = char(i);
			QString strnum = QString(num);
			QString vote = "vote/" + strnum;
			QByteArray data0 = vote.toLatin1();
			char* data = data0.data();
            int length = int(strlen(data));
            _ClientConn->sendData(data, length);
		}
	}
}
void Client::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5)
{
	if (str1 == "connectServer")
	{
        for (QSet<Conn>::const_iterator it = _ServerList -> begin(); it != _ServerList -> end(); ++it)
		{
            if(GetName(*it) == str2)
			{
                bool connect = _ClientConn -> connect(*it);
				if(connect != 0)
					emit sendMessage("server","connectSucceed");
				else
				{
					emit sendMessage("server","connectFailed");
					getServers();
				}
			}
			break;
		}	
	}
	else if (str1 == "getServer")
	{
		getServers();
	}
	else if (str1 == "vote")
	{
        _vote[str2[0].toLatin1()]=1;
		if (_time == 1 && _role == "werewolf")
			sendVote();
	}
	else if (str1 == "cancelVote")
	{
        _vote[str2[0].toLatin1()]=0;
		if (_time == 1 && _role == "werewolf")
		{
            QString vote = "cancelVote/" + str2;
			QByteArray data0 = vote.toLatin1();
			char* data = data0.data();
            int length = int(strlen(data));
            _ClientConn->sendData(data, length);
		}
	}
	else if (str1 == "voteByWitch")
	{
        _witch = str2;
	}
	else if (str1 == "sendChatMessage")
	{
        _message = _message + str2;
	}
	else if (str1 == "assignRoles")
	{
        _role = str2;
	}
	else if (str1 == "day")
	{
		_time = 0;
	}
	else if (str1 == "night")
	{
		_time = 1;
	}
	else if (str1 == "changeName")
	{
        _name = str2;
	}

}
