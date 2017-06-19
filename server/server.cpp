#define DRAW 0
#define WEREWOLF_VICTORY 1
#define VILLIAGER_VICTORY 2
#define LOVERS_VICTORY 3 
#define PIEDPIPER_VICTORY 4

#define WEREWOLF 0
#define TOWNSFOLK 1
#define GOD 2
#define PIEDPIPER 3

#include "server.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>

#include <QMessageBox>

namespace OOPLRS {
namespace server {
	User :: User(int n, int characternum, int pos) : num(n), characterNum(characternum), position(pos), death(false), canVote(true), isPuzzled(false), cannotVoteForever(false)
	{}
	GameEvent :: GameEvent(GameConfig *conf)
	{
		config = conf;
	}
	GameEvent :: GameEvent(const GameEvent& ge)
	{
		config = ge.config;
	}
	GameEvent :: ~GameEvent()
	{
		config = NULL;
	}
	void GameConfig :: setConfig(int playernum, vector<int> character, QString name)
	{
		playerNum = playernum;
		connNum = sheriffNum = 0;
		loseAbility = false;
		idiot = -1;
		canAssign =false;
		for(int i = 0; i < character.size(); i++)
		{
			User u(i, character[i], i);
			user.push_back(u);
			if(character[i] == 11)
			{
				hasThief = 2;
				User uTf1(playernum, 1, -1), uTf2(playernum + 1, 1, -1);
				user.push_back(uTf1);
				user.push_back(uTf2);
			}
			else
				hasThief = 0;
			hasConn[i] = false;
		}
		serverConn = new ServerConn;
		serverConn -> start(name);
	}
    void GameConfig :: clientConnected(Conn remote)
    {
		srand(time(nullptr));
		connNum ++;
		int tmp = rand() % playerNum;
		while(hasConn[tmp])
			tmp = rand() % playerNum;

		connMap[remote] = tmp;
        user[tmp].conn = remote;
		string str("position/");
		str = str + transNumToString(tmp);
		serverConn -> sendData(remote, str.c_str(), (int)strlen(str.c_str()));
		string info("join/");
		for(int i = 0; i < playerNum; i++)
			if(hasConn[i])
				serverConn -> sendData(remote, (info + transNumToString(i) + '/'  + transNumToString(i)).c_str(), (int)strlen((info + transNumToString(i) + '/'  + transNumToString(i)).c_str()));
		serverConn -> broadcast((info + transNumToString(tmp) + '/'  + transNumToString(tmp)).c_str(), (int)strlen((info + transNumToString(tmp) + '/'  + transNumToString(tmp)).c_str()));
		hasConn[tmp] = true;				
        emit onClientChanged();
	}
    void GameConfig :: clientDisconnected(Conn remote)
	{
		connNum --;
		int tmp = connMap[remote];
		hasConn[tmp] = false;
		user[tmp].conn = NULL;

        emit onClientChanged();
	}
    void GameConfig :: clientData(Conn remote, byteseq data, int length)
	{
        string str(data, length);
        user[connMap[remote]].messeges.push_back(str);
	}
	void GameServer :: setConfig(int playernum, vector<int> character, int sheriffselection, int victoryjudge, QString name)
	{
		if(sheriffselection)
			sheriffSelection = new HasSheriffSelection(&config);
		else
			sheriffSelection = new NoSheriffSelection(&config);
		if(victoryjudge)
			victoryJudge = new KillAll(&config);
		else
			victoryJudge = new KillGods(&config);
		config.setConfig(playernum, character, name);
		startGame = new StartGame(&config);
        QObject::connect(config.serverConn, SIGNAL(onClientConnected(Conn)), &config, SLOT(clientConnected(Conn)));
        QObject::connect(config.serverConn, SIGNAL(onClientDisconnected(Conn)), &config, SLOT(clientDisconnected(Conn)));
        QObject::connect(config.serverConn, SIGNAL(onClientData(Conn, byteseq, int)), &config, SLOT(clientData(Conn, byteseq, int)));
	}
	Character* GameServer :: transNumToCharacter(int num)
	{
		Character* chara;
		switch(num)
		{
			case 0: {chara = new Werewolf(&config); break;}
			case 1: {chara = new Townsfolk(&config); break;}
			case 2: {chara = new Ancient(&config); break;}
			case 3: {chara = new Cupid(&config); break;}
			case 4: {chara = new Hunter(&config); break;}
			case 5: {chara = new Idiot(&config); break;}
			case 6: {chara = new Savior(&config); break;}
			case 7: {chara = new Scapegoat(&config); break;}
			case 8: {chara = new Seer(&config); break;}
			case 9: {chara = new Witch(&config); break;}
			case 10: {chara = new PiedPiper(&config); break;}
			case 11: {chara = new Thief(&config); break;}
		}
		return chara;
	}
	int GameServer :: transNumToCharacterType(int num)
	{
		int res;
		if(num == 0)
			res = WEREWOLF;
		else if(num == 1)
			res = TOWNSFOLK;
		else if(num == 10)
			res = PIEDPIPER;
		else
			res = GOD;
		return res;
	}
	void GameServer :: reshuffle()
	{
		srand(time(0));
		int mod1 = config.playerNum + config.hasThief, mod2 = config.playerNum;
		const int reshuffleRound = 10000;
		config.hasCupid = false;
		for(int i = 0; i < reshuffleRound; i++)
		{
			int rd1 = rand() % mod1, rd2 = rand() % mod1;
			swap(config.user[rd1].characterNum, config.user[rd2].characterNum);
		}
		for(int i = 0; i < reshuffleRound; i++)
		{
			int rd1 = rand() % mod2, rd2 = rand() % mod2;
			swap(config.user[rd1].position, config.user[rd2].position);
		}
		if(config.hasThief && (config.user[config.playerNum].characterNum == 11 || config.user[config.playerNum + 1].characterNum == 11))
		{
			config.hasThief = 0;
			config.user.erase((config.user.end()));
			config.user.erase((config.user.end()));
		}
		for(vector<User> :: iterator it = config.user.begin(); (it + config.hasThief) != config.user.end(); it++)
		{
			config.characterNumber[it -> characterNum].push_back(it -> num);
			character.push_back(transNumToCharacter(it -> characterNum));
			character[it -> num] -> num = it -> num;
			config.user[it -> num].characterType = transNumToCharacterType(it -> characterNum);
			if(it -> characterNum == 3)
				config.hasCupid = true;
		}
		config.lovers = new Lovers(0,0,0,0);
		startGame = new StartGame(&config);
		broadcast = new Broadcast(&config);
		gotMessege = new GotMessege(&config);
	}
	bool twoCompare(int a, int b,int c,int d)
	{
		if(a == c && b == d)
			return true;
		if(a == d && b == c)
			return true;
		return false;
	}
	string transNumToString(int num)
	{
        num ++;
		char cc[3];
		if(num < 10)
		{
			cc[0] = num + '0';
			cc[1] = '\0';
		}
		else
		{
			cc[0] = num / 10 + '0';
			cc[1] = num % 10 + '0';
			cc[2] = '\0';
		}
		string st(cc);
		return st;
	}
	int transCharToNum(char cc)
	{
		return cc - 'a' - 1;
	}
	int KillGods :: judgeGen()
	{
		int townsfolkDeath = 1, godDeath = 1;
		for(int i = 0; i < config -> user.size(); i++)
		{
			if(!config -> user[i].death && config -> user[i].characterType == TOWNSFOLK)
				townsfolkDeath = 0;
			if(!config -> user[i].death && config -> user[i].characterType == GOD)
				godDeath = 0;
		}
		return max(townsfolkDeath, godDeath);
	}
	int KillAll :: judgeGen()
	{
		int werewolfWin = 1;
		for(int i = 0; i < config -> user.size(); i++)
			if(!config -> user[i].death && (config -> user[i].characterType == TOWNSFOLK || config -> user[i].characterType == GOD))
				werewolfWin = 0;
		return werewolfWin;
	}
	int VictoryJudge :: judgeSpe()
	{
		bool piedpiperwin = true;
		bool loverswin = true;
		bool villiagerwin = true;
		for(int i = 0; i < config -> user.size(); i++)
		{
			if(!config -> user[i].death && !config -> user[i].isPuzzled && config -> user[i].characterType != PIEDPIPER)
				piedpiperwin = false;
			if(config -> hasCupid)
				if(!config -> user[i].death && i != config -> lovers -> first && i != config -> lovers -> second && i != config -> lovers -> cupidNum)
					loverswin = false;
			if(!config -> user[i].death && config -> user[i].characterType == WEREWOLF)
				villiagerwin = false;
		}
		if(piedpiperwin)
			return PIEDPIPER_VICTORY;
		if(loverswin && config -> hasCupid && config -> lovers ->isWVLove)
			return LOVERS_VICTORY;
		if(villiagerwin)
			return VILLIAGER_VICTORY;
		return DRAW;
	}
	int VictoryJudge :: judge()
	{
		return max(judgeGen(), judgeSpe());
	}
	void Broadcast :: broadcast(const char *info)
	{
		broadcastInfo(info);
	}
	void Character :: killed()
	{
		string info("dead/");
		broadcastInfo((info + transNumToString(num)).c_str());
		config -> user[num].death = true;
		if(config -> hasCupid)
		{
			int lov = -1;
			if(num == config -> lovers -> first)
				lov = config -> lovers -> second;
			else if(num == config -> lovers -> second)
				lov = config -> lovers -> first;
			if(lov != -1)
			{
				config -> user[lov].death = true;
				broadcastInfo((info + transNumToString(lov)).c_str());
			}
		}
	}
	void Vote :: vote()
	{
		show();
		int playerNum = config -> playerNum;
		//cout<<playerNum<<"pl\n";
		vector<int> tmp;
		for(int i = 0; i < playerNum; i++)
		{
			tmp.push_back(0);
			voting.push_back(-1);
        }
		//cout<<"askd\n";
		int flag = 0;
		for(int i = 0; i < playerNum; i++)
        {
			if(canVote(i))
			{
				//cout<<i<<endl;

                string resp;
				if(!flag)
				{
                    resp = respond(i, voteInterval());
					flag = 1;
				}
				else
                    resp = respond(i, 0);

				if(resp[0] != '!')
				{
                    qDebug() << i;
					tmp[transCharToNum(resp[5])]++;
                    qDebug() << "sfaaf" << transCharToNum(resp[5]);
					voting[i] = transCharToNum(resp[5]);
                    qDebug() << i;
				}
				//cout<<transCharToNum(resp[5])<<endl;
			}
            qDebug() << "finish" << i;
        }
		string info("showVoteResult/");
		for(int i = 0; i < playerNum; i++)
			if(voting[i] != -1)
				broadcastInfo((info + transNumToString(i) + '/' + transNumToString(voting[i])).c_str());
		for(int i = 0; i < playerNum; i++)
			res.push_back(make_pair(-tmp[i], i));
		sort(res.begin(),res.end());
		for(int i = 0; i < playerNum; i++)
			res[i].first = -res[i].first;
		if(res[0].first == res[1].first)
			result = ifDraw();
		else
			result = res[0].second;
	}
	bool WerewolfVote :: canVote(int num)
	{
		if(config -> user[num].characterType == WEREWOLF && !config -> user[num].death)
			return true;
		return false;
	}
	int WerewolfVote :: ifDraw()
	{
		vector<int> sel;
		for(int i = 0; i < config -> playerNum; i++)
		{
			if(res[i].first == res[0].first)
				sel.push_back(res[i].second);
			else
				break;
		}
		srand(time(0));
		return sel[rand() % sel.size()];
	}
	void WerewolfVote :: show()
	{
		for(int i = 0; i < config -> playerNum; i++)
			for(int j = 0; j < config -> playerNum; j++)
				if(canVote(i) && canVote(j))
				{
                    QByteArray info = QByteArray("roleAct/");
                    info.append(transNumToString(j).c_str());
                    transferInfoToClient(i, info.data());
				}
		broadcastInfo("setTime/15");
        for(int i = 0; i < config -> playerNum; i++)
            if(canVote(i))
                transferInfoToClient(i, "startVote");
		clock_t cl = clock();
        while(clock() - cl < 15000)
        {
			for(int i = 0; i < config -> playerNum; i++)
				if(canVote(i) && !config -> user[i].messeges.empty())
				{
					for(int j = 0; j < config -> user[i].messeges.size(); j++)
						for(int k =0; k < config -> playerNum; k++)
							if(canVote(k))
								transferInfoToClient(k,( config -> user[i].messeges[j] + '/' + transNumToString(i)).c_str());
					config -> user[i].messeges.clear();
				}
		}
	}
	bool dayVote :: canVote(int num)
	{
		if(!config -> user[num].death && config -> user[num].canVote)
			return true;
		transferInfoToClient(num, "cannotVote");
		return false;
	}
    void dayVote :: show()
    {
        broadcastInfo("startDayVote");
		for(int i = 0; i < config -> playerNum; i++)
            if(canVote(i))
                transferInfoToClient(i, "startVote");
    }
	int dayVote :: ifDraw()
	{
		if(!config -> characterNumber[7].empty() && !config -> loseAbility)
		{
			int scapegoatNum = *(config -> characterNumber[7].begin());
			if(!config -> user[scapegoatNum].death)
			{
				config -> canAssign = true;
				return scapegoatNum;
			}
        }

        return -1;
	}
	void WerewolfOperation :: operation()//0
	{
		//cout<<"3";
		Vote *vote = new WerewolfVote(config);
		//cout<<"2";
		vote -> vote();
		string info("werewolfKill/");
		info = info + transNumToString(vote -> result);
		for(int i = 0; i < config -> playerNum; i++)
			if(vote -> canVote(i))
				transferInfoToClient(i, info.c_str());
		config -> killedPlayer = vote -> result;
	}
	void Ancient :: init()
	{
		hasKilled = false;
	}
	void Ancient :: killedByWerewolf()
	{
		if(!hasKilled)
			hasKilled = true;
		else
			config -> deads.push_back(num);
	}
	void Ancient :: killedByVoting()
	{
		config -> loseAbility = true;
		string info("showCharacter/");
		broadcastInfo((info + transNumToString(num) + "/ancient").c_str());
		broadcastInfo("loseAbility");
		killed();
	}
	void Cupid :: firstNightOperation() //3
	{
		//cout<<"Cupid\n";
		string info1("roleAct");
        transferInfoToClient(num, "startVote");
		transferInfoToClient(num, info1.c_str());
		string resp = respond(num, 20000);
		if(resp[0] == '!')
		{
			config -> hasCupid = 0;
			return ;
		}
		Lovers lov(num, transCharToNum(resp[12]), transCharToNum(resp[14]), twoCompare(config -> user[transCharToNum(resp[12])].characterType,config -> user[transCharToNum(resp[14])].characterType, WEREWOLF, TOWNSFOLK) || twoCompare(config -> user[transCharToNum(resp[12])].characterType,config -> user[transCharToNum(resp[14])].characterType, WEREWOLF, GOD));
		*(config -> lovers) = lov;
		string info2("shotByCupid/");
		transferInfoToClient(lov.first, (info2 + transNumToString(lov.second)).c_str());
		transferInfoToClient(lov.second, (info2 + transNumToString(lov.first)).c_str());
	}
	void Hunter :: killedByWerewolf()
	{
		canShoot = true;
		config -> deads.push_back(num);
	}
	void Hunter :: init()
	{
		canShoot = false;
	}
	void Hunter :: dayOperation()
	{
		if(!canShoot)
			transferInfoToClient(num, "cannotShoot");
		else if(!config -> loseAbility)
		{
			transferInfoToClient(num, "canShoot");
			broadcastInfo("waitingHunter");
			string resp = respond(num, 20000);
            if(resp[0] == '!')
			{
				canShoot = false;
				return;
			}
			killedPlayer = transCharToNum(resp[5]);
			string info2("showCharacter/");
			broadcastInfo((info2 + transNumToString(num) + "/hunter").c_str());
			config -> deads.push_back(killedPlayer);
		}
		else
			transferInfoToClient(num, "roleActLoseAbility");
		canShoot = false;
	}
	void Idiot :: killedByVoting()
	{
		if(config -> loseAbility)
		{
			transferInfoToClient(num, "roleActLoseAbility");
			return;
		}
		config -> user[num].canVote = false;
		config -> user[num].cannotVoteForever = true;
		string info2("showCharacter/");
		broadcastInfo((info2 + transNumToString(num) + "/idiot").c_str());
	}
	void Savior :: init()
	{
		lastSavee = -1;
		config -> lastSavee = -1;
	}
	void Savior :: nightTransferInfo1()//6
	{
		//cout<<"Savior\n";
		if(config -> loseAbility)
		{
			transferInfoToClient(num, "roleActLoseAbility");
			return;
		}
		string info("roleAct/");
		transferInfoToClient(num, (info + transNumToString(lastSavee)).c_str());
        transferInfoToClient(num, "startVote");
		lastSavee = -1;
	}
	void Savior :: processInfo()
	{
		if(config -> loseAbility)
		{
			return;
		}
		string resp = respond(num, 0);
		if(resp[0] == '!')
		{
			lastSavee = -1;
		}
		else
			lastSavee = transCharToNum(resp[5]);
		config -> lastSavee = lastSavee;
	}
	void Scapegoat :: killedByVoting() {}//7
	void Seer :: nightOperation()
	{
		if(config -> loseAbility)
		{
			transferInfoToClient(num, "roleActLoseAbility");
			return;
		}
		transferInfoToClient(num ,"roleAct");
        transferInfoToClient(num, "startVote");
        string resp = respond(num, 15000);
		if(resp[0] == '!')
			return;
		int tmp = 1;
		if(config -> user[transCharToNum(resp[5])].characterType == WEREWOLF)
			tmp = 0;
		string info("showIdentity/");
		transferInfoToClient(num, (info + transNumToString(transCharToNum(resp[5])) + '/' + (char)('0' + tmp)).c_str());
	}
	void Witch :: init()
	{
		hasPoison = 1;
		hasMedicine = 1;
	}
	void Witch :: nightTransferInfo2()//9
	{
		if(config -> loseAbility)
		{
			transferInfoToClient(num, "roleActLoseAbility");
			return;
		}
		string info("roleAct/");
		transferInfoToClient(num, (info + transNumToString(config -> killedPlayer) + '/' + (char)(hasPoison + '0') + (char)(hasMedicine + '0')).c_str());
        transferInfoToClient(num, "startVote");
    }
	void Witch :: processInfo()
	{
		if(config -> loseAbility)
		{
			return;
		}
		vector<string> infos= manyRespond(num, 0);
		for(int i = 0; i < infos.size(); i++)
		{
			string resp = infos[i];
			if(resp[12] != '0')
			{
				if(resp[12] == '1')
				{
					config -> poisonedPlayer = transCharToNum(resp[14]);
					//cout<<config -> poisonedPlayer<<endl;
					hasPoison = 0;
				}
				else if(resp[12] == '2')
				{
					config -> savedPlayer = transCharToNum(resp[14]);
					hasMedicine = 0;
				}
			}
		}
	}
	void PiedPiper :: nightTransferInfo1() {}
	void PiedPiper :: processInfo() {};//10
	void Thief :: firstNightOperation()//11
	{
		string a("roleAct/");
		a = a + characterName[config -> user[config ->playerNum].characterNum] + '/' + characterName[config -> user[config ->playerNum + 1].characterNum];
		transferInfoToClient(num, a.c_str());
		//cout<<a<<endl;
		string b = respond(num, 20000);
		//cout<<b<<endl;
		if(b[0] =='!' || b[12] == '0')
			config -> user[num].characterNum = 1;
		else
			config -> user[num].characterNum = config -> user[config ->playerNum + b[12] - '1'].characterNum;
		//cout<<"w";
		config -> user.erase(config -> user.end());
		config -> user.erase(config -> user.end());
		string c("thiefChooseResult");
		transferInfoToClient(num, (c + characterName[config -> user[num].characterNum]).c_str());
		if(config -> user[num].characterNum == 3)
			config -> hasCupid = true;
		config -> characterNumber[config -> user[num].characterNum].push_back(num);
	}
    int HasSheriffSelection :: selection() { return 0; }
	void StartGame :: startGame()
	{
		string s1("start");
		string s2("assignRoles/");
		for(vector<User> :: iterator it = config -> user.begin(); (it + config -> hasThief) != config -> user.end(); it++)
		{
			//cout<< GameEvent :: config -> playerNum << endl;
			transferInfoToClient(it -> num, s1.c_str());
			transferInfoToClient(it -> num,(s2 + characterName[it -> characterNum]).c_str());
		}
	}
	void GotMessege :: gotMessege(int num, bool islastword)
	{
		string info1("start"), info2("show");
		if(islastword)
		{
            info1 = info1 + "LastWords/";
            info2 = info2 + "LastWords/";
		}
		else
		{
			info1 = info1 + "Chat/";
			info2 = info2 + "ChatMessage/";
		}
        broadcastInfo((info1 + transNumToString(num)).c_str());
        info2 = info2 + transNumToString(num) + '/';
        string resp = respond(num, 20000, false);
        qDebug() << QByteArray(resp.c_str());
		char messege[3001];
        if(resp[0] != '!')
        {
            strcpy(messege, resp.c_str());
            info2 = info2 + messege;
        }
		broadcastInfo(info2.c_str());
		clock_t cl = clock();
		while(clock() - cl < 1000) ;
    }

	int GameServer :: day(bool isFirstDay)
	{
		//cout<<config.deads.size()<<"size"<<endl;
		for(int i = 0 ; i < config.deads.size(); i++)
            character[config.deads[i]] -> killed();
		for(int i = 0 ; i < config.deads.size(); i++)
            if(isFirstDay)
				gotMessege -> gotMessege(config.deads[i], true);
		if(victoryJudge -> judge())
				return victoryJudge -> judge();
		config.deads.clear();
		//cout<<"w\n";
		for(int i = 0 ; i < config.playerNum; i++)
				character[i] -> dayOperation();
		//cout<<"w\n";
		
		if(!config.deads.empty())
		{
			//cout<<config.deads[0]<<endl;
			character[config.deads[0]] -> killed();
			config.deads.clear();
		}
		if(victoryJudge -> judge())
				return victoryJudge -> judge();
		for(int i = 0 ; i < config.playerNum; i++)
			if(!config.user[i].death)
				gotMessege -> gotMessege(i, false);
		Vote* vote = new dayVote(&config);
		vote -> vote();
		int deadPlayer = vote -> result;
		for(int i = 0; i < config.playerNum; i++)
			if(!config.user[i].cannotVoteForever)
				config.user[i].canVote = true;
		if(deadPlayer != -1)
		{
        	character[deadPlayer] -> killedByVoting();
        	gotMessege -> gotMessege(deadPlayer, true);
		}
        return 0;
	}
	void GameServer :: night()
	{
		config.savedPlayer = config.poisonedPlayer = config.killedPlayer = config.lastSavee = -1;
		for(vector<Character*> :: iterator it = character.begin(); it != character.end(); it++)
				(*it) -> nightTransferInfo1();
		//cout<<"1"<<endl;
		WerewolfOperation w(&config);
		//cout<<"1"<<endl;
		w.operation();
		//cout<<config.killedPlayer <<"kp\n";
		for(vector<Character*> :: iterator it = character.begin(); it != character.end(); it++)
				(*it) -> nightTransferInfo2();
		clock_t cl = clock();
		for(vector<Character*> :: iterator it = character.begin(); it != character.end(); it++)
				(*it) -> nightOperation();
		bool flag  = false;
		while(clock() - cl < 15000) 
			if(!flag)
			{
				flag = true;
				broadcast -> broadcastInfo("setTime/15");
			}
		for(vector<Character*> :: iterator it = character.begin(); it != character.end(); it++)
				(*it) -> processInfo();
		if(((config.savedPlayer == config.lastSavee && config.savedPlayer != -1) || (config.lastSavee != config.killedPlayer && config.savedPlayer != config.killedPlayer) )&& config.killedPlayer != -1)
			character[config.killedPlayer] -> killedByWerewolf();
		//cout<<config.poisonedPlayer<<endl;
		if(config.poisonedPlayer != -1)
			config.deads.push_back(config.poisonedPlayer);
	}
	int GameServer :: firstDay()
	{
		broadcast -> broadcast("day");
		for(int i = 0; i < config.playerNum; i++)
			if(!config.user[i].cannotVoteForever)
				config.user[i].canVote = true;
		return day(true);
	}
	void GameServer :: firstNight()
	{
		broadcast -> broadcast("night");
		if(config.hasThief)
		{
			character[*(config.characterNumber[11].begin())] -> firstNightOperation();
			//cout<<*(config.characterNumber[11].begin())<<endl;
			character[*(config.characterNumber[11].begin())] = transNumToCharacter(config.user[*(config.characterNumber[11].begin())].characterNum);
			character[*(config.characterNumber[11].begin())] -> num = *(config.characterNumber[11].begin());
			config.characterNumber[11].clear();
		}
		//cout<<"w";
		if(config.hasCupid)
			character[*(config.characterNumber[3].begin())] -> firstNightOperation();
		for(int i = 0; i < config.playerNum; i++)
			character[i] -> init();
		//cout<<"w";
		night();
	}
	int GameServer :: mainProcess()
	{
		int v;
		firstNight();
		//character[*config.characterNumber[4].begin()] -> killedByWerewolf();
		if(victoryJudge -> judge())
			return victoryJudge -> judge();
		v = firstDay();
		if(v)
			return v;
		if(victoryJudge -> judge())
			return victoryJudge -> judge();
		while(1)
		{
			broadcast -> broadcast("night");
			night();
			broadcast -> broadcast("day");
			if(victoryJudge -> judge())
				return victoryJudge -> judge();
			v = day(false);
			if(v)
				return v;
			if(victoryJudge -> judge())
				return victoryJudge -> judge();
		}
	}
	void GameServer :: endGame(int winCode)
	{
		string info1("showWin/"),info2("win/");
		broadcast -> broadcast((info1 + transNumToString(winCode)).c_str());
        for(int i = 0; i < config .playerNum; i++)
        {
            qDebug() << i;
            if((winCode == WEREWOLF_VICTORY && config.user[i].characterType == WEREWOLF) || (winCode == VILLIAGER_VICTORY && (config.user[i].characterType == GOD || config.user[i].characterType == TOWNSFOLK) && !(config.hasCupid && config.lovers -> isWVLove && (i == config.lovers -> first || i == config.lovers -> second))) || ((winCode == LOVERS_VICTORY && config.lovers -> isWVLove && (i == config.lovers -> first || i == config.lovers -> second))) || (winCode = PIEDPIPER_VICTORY && config.user[i].characterType == PIEDPIPER))
				broadcast -> broadcast((info2 + transNumToString(i)).c_str());
            qDebug() << i;
        }
        qDebug() << "ok";
		broadcast -> broadcast("endGame");
		config.serverConn -> close();
	}
}
}
