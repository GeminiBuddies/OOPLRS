#pragma once

#ifndef SERVER_H
#define SERVER_H
#include "..\cih\globalConf.h"
#include "serverconn.h"
#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <map>
#include <QObject>
#include <QThread>
#define WAIT 100
using namespace std;

namespace OOPLRS {
namespace server {
	const int characterN = 12;
	const string characterName[characterN] = {"werewolf", "townsfolk", "ancient", "cupid", "hunter", "idiot", "savior", "scapegoat", "seer", "witch", "piedPiper", "thief"};
/*	class ClientUser
	{
	public:
		int num;
		int characterNum;
		Conn* conn;
		void setting(int n,int characternum)
		{
			num = n;
			characterNum = characternum;
		}
		void printMessege()
		{
			cout << "User No." << num << endl;
			for(vector<string> :: iterator i = messege.begin(); i != messege.end(); i++)
				cout << *i << endl;
			cout << endl;
		}
		string respond(int timeInterval, bool isRoleAct = true)
		{
			printMessege();
			cout << "please respond\n";
			string cc;
			cin >> cc;
			return cc;
		}
	};*/
	string transNumToString(int num);
	int transCharToNum(char cc);
	bool twoCompare(int a, int b,int c,int d);
	class Lovers
	{
	public:
		bool isWVLove;
		int first;
		int second;
		int cupidNum;
        Lovers(int cupidnum, int f, int s, bool iswvlove) : cupidNum(cupidnum), first(f), second(s), isWVLove(iswvlove) {}
	};
	class User
	{
	public:
		int num;
		int characterNum;
		int position;
		bool death;
		bool canVote;
		bool isPuzzled;
		bool cannotVoteForever;
		int characterType;
        Conn conn;
		vector<string> messeges;
		User(int n, int characternum, int pos);
	};
    class GameConfig : public QObject
	{
        Q_OBJECT
	public:
		int playerNum;
		vector<User> user;
		vector<int> characterNumber[characterN];
		vector<int> positionOrder;
		int sheriffNum;
		bool loseAbility;
		bool hasCupid;
		int hasThief;
		int lastSavee;
		int poisonedPlayer;
		int savedPlayer;
		int killedPlayer;
		int idiot;
		bool canAssign;
		vector<int> deads;
		Lovers *lovers;
		ServerConn* serverConn;
		map<Conn, int> connMap;
		bool hasConn[100];
		int connNum;
		//GameState() : sheriffNum(0), loseAbility(false) {};
		void setConfig(int playernum, vector<int> character, QString name);//统计各角色数量及编号
    public slots:
        void clientConnected(Conn remote);
        void clientDisconnected(Conn remote);
        void clientData(Conn remote, byteseq data, int length);

    signals:
        void onClientChanged();
	};
    
	class GameEvent
	{
	public:
		GameConfig *config;
		char* transInfo;
		int infoLen;
	public:
		GameEvent(){}
		GameEvent(GameConfig *conf);
		GameEvent(const GameEvent& ge);
		~GameEvent();
		void transferInfoToClient(int userName, const char *info)
		{
                qDebug() << "send to" << userName << "info" << info;
                config -> serverConn -> sendData(config -> user[userName].conn, info, (int)strlen(info));
		}
		void broadcastInfo(const char *info)
		{
            config -> serverConn -> broadcast(info, (int)strlen(info));
		}
        string respond(int userName,int timeInterval, bool isRoleAct = true)
		{
			if(timeInterval != 0)
			{
				string info("setTime/");
                broadcastInfo((info + transNumToString(timeInterval / 1000 - 1)).c_str());
			}
			clock_t cl = clock();
            while(clock() - cl < timeInterval) ;
			if(isRoleAct)
				transferInfoToClient(userName, "roleActEnd");
            else{
                transferInfoToClient(userName, "getMessege");
                        qDebug() << "getMessege";}
			cl = clock();
            while(clock() - cl < WAIT) ;
			if(config -> user[userName].messeges.empty())
			{
				string res("!");
				return res;
			}
			else
            {
                qDebug() << userName << "to" << QByteArray(config -> user[userName].messeges[config -> user[userName].messeges.size() - 1].c_str());
                string res = config -> user[userName].messeges[config -> user[userName].messeges.size() - 1];
				config -> user[userName].messeges.clear();
				return res;
			}
		}
		vector<string> manyRespond(int userName,int timeInterval, bool isRoleAct = true)
		{
			if(timeInterval != 0)
			{
				string info("setTime/");
                broadcastInfo((info + transNumToString(timeInterval / 1000 - 1)).c_str());
			}
			clock_t cl = clock();
            while(clock() - cl < timeInterval) ;
			if(isRoleAct)
				transferInfoToClient(userName, "roleActEnd");
			else
				transferInfoToClient(userName, "getMessage");
			cl = clock();
            while(clock() - cl < WAIT) ;
			vector<string> res = config -> user[userName].messeges;
			config -> user[userName].messeges.clear();
			return res;
		}
	};
	class Vote : public GameEvent
	{
	public:
		vector<pair<int,int> > res;
		vector<int> voting;
		int result;
		using GameEvent :: GameEvent;
		void vote();
		virtual bool canVote(int num) = 0;
		virtual int ifDraw() = 0;
		virtual void show() = 0;
		virtual int voteInterval(){return 20000;}
	};
	class WerewolfVote : public Vote
	{
	public:
		using Vote :: Vote;
		bool canVote(int num);
		int voteInterval(){return 0;}
		int ifDraw();
		void show();
	};
	class dayVote : public Vote
	{
	public:
		using Vote :: Vote;
		bool canVote(int num);
		int ifDraw();
        void show();
	};
	class StartGame : public GameEvent
	{
	public:
		using GameEvent :: GameEvent;
		void startGame();
	};
	class Broadcast : public GameEvent
	{
	public:
		using GameEvent :: GameEvent;
		void broadcast(const char *info);
	};
	class WerewolfOperation : public GameEvent
	{
	public:
		using GameEvent :: GameEvent;
		int killedPlayer;
		void operation();
	};
	class GotMessege : public GameEvent
	{
	public:
		using GameEvent :: GameEvent;
		void gotMessege(int num, bool islastword);
	};
	class Character : public GameEvent
	{
	public:
		using GameEvent :: GameEvent;
		int num;
        virtual void nightTransferInfo1() {}
        virtual void nightTransferInfo2() {}
        virtual void processInfo() {}
        virtual void nightOperation() {}
        virtual void firstNightOperation() {}
        virtual void dayOperation() {}
        virtual void killed();
        virtual void killedByWerewolf() {config -> deads.push_back(num);}
        virtual void killedByVoting(){killed();}
        virtual void init(){}
	};
	class Werewolf : public Character
	{
	public:
		using Character :: Character;
	};
	class Townsfolk : public Character
	{
	public:
		using Character :: Character;
	};
	class Ancient : public Character
	{
	public:
		using Character :: Character;
		bool hasKilled;
		void init();
		void killedByWerewolf();
		void killedByVoting();
	};
	class Cupid : public Character
	{
	public:
		using Character :: Character;
		void firstNightOperation();
	};
	class Hunter : public Character
	{
	public:
		using Character :: Character;
		bool canShoot;
		int killedPlayer;
		void killedByWerewolf();
		void init();
		void dayOperation();
	};
	class Idiot : public Character
	{
	public:
		using Character :: Character;
		void killedByVoting();
	};
	class Savior : public Character
	{
	public:
		using Character :: Character;
		int lastSavee;
		void init();
		void nightTransferInfo1();
		void processInfo();
	};
	class Scapegoat : public Character
	{
	public:
		using Character :: Character;
		void killedByVoting();
	};
	class Seer : public Character
	{
	public:
		using Character :: Character;
		void nightOperation();
	};
	class Witch : public Character
	{
	public:
		using Character :: Character;
		int hasPoison;
		int hasMedicine;
		void nightTransferInfo2();
		void init();
		void processInfo();
	};
	class PiedPiper : public Character
	{
	public:
		using Character :: Character;
		void nightTransferInfo1();
		void processInfo();
	};
	class Thief : public Character
	{
	public:
		using Character :: Character;
		void firstNightOperation();
	};
	class VictoryJudge : public GameEvent
	{
	public:
		using GameEvent :: GameEvent;
		virtual int judgeGen() = 0;
		int judgeSpe();
		int judge();
		//0 means no, 1 means werewolf victory, 2 means villiagers victory
	};
	class KillGods : public VictoryJudge
	{
	public:
		using VictoryJudge :: VictoryJudge;
		int judgeGen();
	};
	class KillAll : public VictoryJudge
	{
	public:
		using VictoryJudge :: VictoryJudge;
		int judgeGen();
	};
	class SheriffSelection :public GameEvent
	{
	public:
		using GameEvent :: GameEvent;
		virtual int selection() = 0;
	};
	class NoSheriffSelection : public SheriffSelection
	{
	public:
		using SheriffSelection :: SheriffSelection;
        int selection() {return 0;}
	};
	class HasSheriffSelection : public SheriffSelection
	{
	public:
		using SheriffSelection :: SheriffSelection;
		int selection();
	};
    class GameServer {
	public://得改
        GameConfig config;
		vector <Character*> character;
		SheriffSelection *sheriffSelection;
		VictoryJudge *victoryJudge;
        GameServer() {};
		StartGame *startGame;
		Broadcast *broadcast;
		GotMessege *gotMessege;
		Character* transNumToCharacter(int num);
		int transNumToCharacterType(int num);
        void setConfig(int playernum, vector<int> character, int sheriffselection, int victoryjudge, QString name);
		void reshuffle();
		int day(bool isFirstDay);
		void night();
		int firstDay();
		void firstNight();
		int mainProcess();
		void endGame(int winCode);
    };
}
}
#endif
