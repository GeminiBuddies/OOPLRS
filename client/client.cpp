/*************************************************
名称 : client。cpp
作者 : 时英天
时间 : 2017-06-23
内容描述 : client类中函数的实现
版权 : 这是我们自己完成的程序，没有使用其余来源代码。
*************************************************/
#include "messager.h"
#include <QObject>
#include <QSet>
#include <QString>
#include <cstring>
#include "client.h"
/*
*功能 : client类的构造函数，用于设置玩家的一些初始信息
*参数:
*	player：一个Messager类的指针
*	name：玩家名字的字符串
*/
Client::Client(Messager* player, QString name)
{
	_player = player;
    QObject::connect(_ClientConn, SIGNAL(onServerData(byteseq,int)), this, SLOT(onClientData(byteseq,int)));//服务器端信息槽链接
    QObject::connect(_ClientConn, SIGNAL(onServerDisconnect()), this, SLOT(onClientDisconnect()));          //断线提醒的信号槽链接
	_name = name;
	_ClientConn -> start(_name);                                                                            //开始游戏
	getServers();  																							//获取服务器列表
}
/*
*功能 : 获取断线信息并进行提醒
*/
void Client::onClientDisconnect()
{
	emit sendMessage("server", "disconn");																	//向客户端发送信息
    _ClientConn->close();																					//关闭游戏
}
/*
*功能 : 获取服务器列表
*/
void Client::getServers()
{
	_ServerList = _ClientConn -> getServers();																
	_ServerListname = "";																					//一个QString用于储存服务器名称
    for (QSet<Conn>::const_iterator it = _ServerList -> begin(); it != _ServerList -> end(); ++it)			//通过获取服务器名称的QSet把服务器名称依次储存下来
    {
		if(it != _ServerList -> end() - 1)
        _ServerListname = _ServerListname + GetName(*it) + "-";
		else 
        _ServerListname = _ServerListname + GetName(*it);
	}
    emit sendMessage("server", "serverList", _ServerListname);												//把服务器名称发送给玩家
}
/*
*功能 : 从服务器获取消息并处理
*参数 :
*	data: 一个char*类型的指针，存储信息
*	length: 一个整数，记录数组长度
*/
void Client::onClientData(byteseq data, int length)
{
	int pos[2];																								//一个数组，用于记录分隔符的位置
	pos[0] = 0;
	pos[1] = 0;
	int n = -1;
    QString str1 = "";																						//三个字符串，用于记录分割后的字符串
    QString str3 = "";
    QString str2 = "";
	for (int i = 0; i < length; ++i)																		//遍历寻找分隔符
    {
		if(data[i] == '/')
		{
			n++;
			pos[n] = i;
		}
	}
	if (n == -1)																							//无分隔符情况
	{
        for(int i=0;i<length;i++){
            str1+=data[i];
        }
	}
	else if (n == 0)																						//一个分隔符情况
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
    else if (n == 1)																						//两个分隔符情况
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
	//分割信息后，下面判断信息进行处理
	if (str1 == "roleActEnd")																				//收到行动结束信息	，发送投票信息																		
	{
        emit sendMessage(str1,str2,str3);
        if (_role == "witch" && _time == 1)																	//女巫在晚上的活动特别考虑
		{
            if (_witch == "0")
            {
                QString vote = "vote/0";
                QByteArray data0 = vote.toLatin1();															//把QString转换成char*
                char* data = data0.data();
                int length = int(strlen(data));
                _ClientConn->sendData(data, length);														//向服务器发送消息
            }
            else
            {
                for (int i = 0; i < 200; ++i)																//遍历投票数组，反馈投票的编码
                {

                    if (_vote[i] == 1)
                    {
					char num = char(i);
					QString strnum = QString(num);
                    QString vote = "voteByWitch/" + _witch +"/"+ strnum;
					QByteArray data0 = vote.toLatin1();
					char* data = data0.data();
                    int length = int(strlen(data));
                    _ClientConn->sendData(data, length);
                    break;
                    }
                }
            }
        }
		else
			sendVote();																						//非女巫直接发送投票结果
		for (int i = 0; i < 200; ++i)																		//将投票数组置0
		{
			_vote[i] = 0;
		}
	}
    else if (str1 == "roleAct" && _time == 0)																//过滤信息
	{
		
	}
    else if (str1 == "showVoteResult" && _role != "werewolf" && _time == 1)
	{
		
	}
    else
        emit sendMessage(str1,str2,str3);																	//把分割后的信息交由角色类处理
}
/*
*功能 : 发送该玩家的投票信息
*/
void Client::sendVote()
{
	for (int i = 0; i < 200; ++i)																			//遍历投票数组，查找投票编码
	{
		if (_vote[i] == 1)
		{
			char num = char(i);
			QString strnum = QString(num);
			QString vote = "vote/" + strnum;
			QByteArray data0 = vote.toLatin1();																//把QString转换为char*
			char* data = data0.data();
            int length = int(strlen(data));
            _ClientConn->sendData(data, length);															//向服务器发送消息
		}
	}
}
/*
*功能 : 从客户端获取消息并处理
*参数:
*str1 - str5 : 五个QString字符串用于记录信息
*/
void Client::receiveMessage(QString str1, QString str2, QString str3, QString str4, QString str5)
{
	if (str1 == "connectServer")																			//连接服务器
	{
        for (QSet<Conn>::const_iterator it = _ServerList -> begin(); it != _ServerList -> end(); ++it)		//遍历已经获取的服务器列表寻找同名服务器
		{
            if(GetName(*it) == str2)
			{
                bool connect = _ClientConn -> connect(*it);													//连接服务器
				if(connect != 0)
					emit sendMessage("server","connectSucceed");											//连接成功
				else
				{
					emit sendMessage("server","connectFailed");												//连接失败并重新获取服务器列表，反馈给玩家
					getServers();
				}
			}
			break;
		}	
	}
	else if (str1 == "getServer")																			//玩家刷新服务器列表
	{
		getServers();
	}
	else if (str1 == "vote")																				//玩家进行投票
	{
        _vote[str2[0].toLatin1()]=1;
		if (_time == 1 && _role == "werewolf")																//狼人杀人的投票信息进行实时反馈
			sendVote();
	}
	else if (str1 == "cancelVote")																			//玩家取消上次投票
	{
        _vote[str2[0].toLatin1()]=0;
		if (_time == 1 && _role == "werewolf")                                                              //狼人杀人的取消投票信息进行实时反馈
		{
            QString vote = "cancelVote/" + str2;
			QByteArray data0 = vote.toLatin1();
			char* data = data0.data();
            int length = int(strlen(data));
            _ClientConn->sendData(data, length);
		}
	}
	else if (str1 == "voteByWitch")																			//女巫选择毒药、解药、不用药
	{
        _witch = str2;
	}
	else if (str1 == "sendChatMessage")																		//储存聊天信息
	{
        QString info = str2;
        QByteArray data0 = info.toLatin1();																//把QString转换为char*
        char* data = data0.data();
        int length = int(strlen(data));
        _ClientConn->sendData(data, length);
	}
	else if (str1 == "assignRoles")																			//获取当前玩家的角色信息
	{
        _role = str2;
	}
	else if (str1 == "day")																					//更改时间为白天
	{
		_time = 0;
	}
	else if (str1 == "night")																				//更改时间为黑夜
	{
		_time = 1;
	}
	else if (str1 == "changeName")																			//玩家修改用户名
	{
        _name = str2;
	}
    else if (str1 == "info")
    {
        QString info = str2+"/"+str3;
        QByteArray data0 = info.toLatin1();																//把QString转换为char*
        char* data = data0.data();
        int length = int(strlen(data));
        _ClientConn->sendData(data, length);
    }
    else if (str1 == "thiefChoose")
    {
        QString info = str1+"/"+str2;
        QByteArray data0 = info.toLatin1();																//把QString转换为char*
        char* data = data0.data();
        int length = int(strlen(data));
        _ClientConn->sendData(data, length);
    }else
    {
        QString info = str1;
        QByteArray data0 = info.toLatin1();																//把QString转换为char*
        char* data = data0.data();
        int length = int(strlen(data));
        _ClientConn->sendData(data, length);
    }

}

