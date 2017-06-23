/************************************************* 
名称 : client.h
作者 : 时英天
时间 : 2017-06-23
内容描述 : Client类的声明
版权 : 这是我们自己完成的程序，没有使用其余来源代码。
*************************************************/
#ifndef CLIENT_H
#define CLIENT_H

#include "../cih/globalConf.h"
#include "messager.h"
#include <QObject>
#include <QSet>
#include <QString>
#include "clientconn.h"
#include "messager.h"
//Client类负责客户端和服务器之间信息的传递和处理
class Client : public Messager
{
	Q_OBJECT
	Messager* _player;																							//Massager类的指针，用于向客户端传递消息
    ClientConn* _ClientConn = new ClientConn;																	//ClientConn类的指针，用于连接服务器，与服务器之间的交互
	Conn _server;																								//Conn类的对象，用于记录当前连接的服务器
    QString _name;																								//QString类型的字符串，用于记录用户名
    const QSet<Conn>* _ServerList;																				//Qset类型，用于记录当前服务器列表
	QString _ServerListname;																					//QString类型的字符串，用于记录当前所有服务器并发送给玩家
	QString _role;																								//QString类型的字符串，用于记录当前玩家的角色
	QString _message = "";																						//QString类型的字符串，用于记录玩家聊天信息
	QString _witch;																								//QString类型的字符串，用于记录女巫的选择（毒药/解药/不用药）
	bool _vote[200];																							//bool数组，用于记录该玩家的投票结果
	bool _time = 0;																								//bool类型的数，用于记录当前的时间状态（白天/黑夜）
public:
	Client(Messager* player, QString name);																		//该类的构造函数，确定用户名，并与一个玩家类链接
	void getServers();																							//获取服务器列表
	void sendVote();																							//发送投票信息
public slots:
	void onClientData(byteseq data, int length);																//信号槽函数，用于获取服务器信息并处理
    void onClientDisconnect();																					//信号槽函数，用于获取断线信息并处理
    void receiveMessage(QString str1, QString str2="", QString str3="", QString str4="", QString str5="");		//信号槽函数，用于获取客户端信息并处理
};

#endif 
