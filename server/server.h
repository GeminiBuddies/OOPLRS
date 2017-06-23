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
#include <QString>
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
    int transNumToCharacterType(int num);
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
		vector<QString> messeges;
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
		bool hasStartedGame;
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
		void broadcastInfo(const char *info);
		void transferInfoToClient(int userName, const char *info);
        string respond(int userName,int timeInterval);
		vector<string> manyRespond(int userName,int timeInterval, bool isRoleAct = true);
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
		virtual bool canBeVoted(int num) {return true;}
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
	class SheriffVote : public Vote
	{
	public:
		vector<int> canVoting, isCandidate;
		bool isDraw;
		using Vote :: Vote;
		bool canVote(int num);
		int ifDraw();
        void show();
		bool canBeVoted(int num);
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
	class Wake : public GameEvent
	{
	public:
		using GameEvent :: GameEvent;
		void wake();
    };
	class SheriffChooseOrder : public GameEvent
	{
	public:
		vector<int> order;
		using GameEvent :: GameEvent;
		void sheriffChooseOrder(int onedead);
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
		vector<int> gotMessege(int num, bool islastword, bool isSheriffVote = false);
	};
	class Character : public GameEvent
	{
	public:
		using GameEvent :: GameEvent;
		int num;
        virtual void nightTransferInfo() {}
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
		void processInfo();
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
		void nightTransferInfo();
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
		void nightTransferInfo();
		void init();
		void processInfo();
	};
	class PiedPiper : public Character
	{
	public:
		using Character :: Character;
		void nightTransferInfo();
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
		virtual void selection() = 0;
	};
	class NoSheriffSelection : public SheriffSelection
	{
	public:
		using SheriffSelection :: SheriffSelection;
        void selection() {;}
	};
	class HasSheriffSelection : public SheriffSelection
	{
	public:
		using SheriffSelection :: SheriffSelection;
		void selection();
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
