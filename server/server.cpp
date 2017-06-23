#define DRAW 0
#define WEREWOLF_VICTORY 2
#define VILLIAGER_VICTORY 1
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
		connNum =  0;
		sheriffNum = -1;
		loseAbility = false;
		idiot = -1;
		canAssign = false;
		hasStartedGame = false;
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
		if(!hasStartedGame)
		{
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
		}
		else
		{
			//if(connNum == playerNum)
			//	serverConn -> endAcceptConnection();
            hasConn[connMap[remote]] = true;
            user[connMap[remote]].conn = remote;
		}
        emit onClientChanged();
	}
    void GameConfig :: clientDisconnected(Conn remote)
	{
		connNum --;
		int tmp = connMap[remote];
		hasConn[tmp] = false;
		user[tmp].conn = NULL;
        if(!hasStartedGame)
			connMap.erase(remote);
        //else if(hasStartedGame && connNum == playerNum - 1)
		//	serverConn -> beginAcceptConnection();
        emit onClientChanged();
	}
    void GameConfig :: clientData(Conn remote, byteseq data, int length)
    {
        QString str(data);
        str.truncate(length);
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
    int transNumToCharacterType(int num)
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
		if(num < 0)
		{
			string st("-1");
			return st;
		}
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
	void GameEvent :: broadcastInfo(const char *info)
	{
		config -> serverConn -> broadcast(info, (int)strlen(info));
	}
	void GameEvent :: transferInfoToClient(int userName, const char *info)
	{
        qDebug() << "send to" << userName << "info" << info;
		if(config -> hasConn[userName])
					config -> serverConn -> sendData(config -> user[userName].conn, info, (int)strlen(info));
		else if(config -> user[userName].death == false)
		{
			string info("dead/"), info2("disconnected/");
			broadcastInfo((info2 + transNumToString(userName)).c_str());
			broadcastInfo((info + transNumToString(userName)).c_str());
            config -> user[userName].death = true;
		}
	}
    string GameEvent :: respond(int userName,int timeInterval)
	{
		if(timeInterval != 0)
		{
			string info("setTime/");
			broadcastInfo((info + transNumToString(timeInterval / 1000 - 1)).c_str());
		}
		clock_t cl = clock();
        while(clock() - cl < timeInterval) ;
		transferInfoToClient(userName, "roleActEnd");
		cl = clock();
        while(clock() - cl < WAIT) ;
		if(config -> user[userName].messeges.empty())
		{
			string res("!");
			return res;
		}
		else
        {
                //qDebug() << userName << "to" << QByteArray(config -> user[userName].messeges[config -> user[userName].messeges.size() - 1].c_str());
            string res = config -> user[userName].messeges[config -> user[userName].messeges.size() - 1].toStdString();
			config -> user[userName].messeges.clear();
			return res;
		}
	}
    vector<string> GameEvent :: manyRespond(int userName,int timeInterval, bool isRoleAct)
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
		vector<string> res;
		for(int i = 0; i < config -> user[userName].messeges.size(); i++)
			res.push_back(config -> user[userName].messeges[i].toStdString());
		config -> user[userName].messeges.clear();
		return res;
	}
	int KillGods :: judgeGen()
	{
        int townsfolkDeath = WEREWOLF_VICTORY, godDeath = WEREWOLF_VICTORY;
		for(int i = 0; i < config -> user.size(); i++)
		{
			if(!config -> user[i].death && config -> user[i].characterType == TOWNSFOLK)
				townsfolkDeath = DRAW;
			if(!config -> user[i].death && config -> user[i].characterType == GOD)
				godDeath = DRAW;
		}
		return max(townsfolkDeath, godDeath);
	}
	int KillAll :: judgeGen()
	{
		int werewolfWin = WEREWOLF_VICTORY;
		for(int i = 0; i < config -> user.size(); i++)
			if(!config -> user[i].death && (config -> user[i].characterType == TOWNSFOLK || config -> user[i].characterType == GOD))
				werewolfWin = DRAW;
		return werewolfWin;
	}
	int VictoryJudge :: judgeSpe()
	{
		bool piedpiperwin = true;
		bool loverswin = true;
		bool villiagerwin = true;
		int res = DRAW;
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
			res = max(res, PIEDPIPER_VICTORY);
		if(loverswin && config -> hasCupid && config -> lovers ->isWVLove)
			res = max(res, LOVERS_VICTORY);
		if(villiagerwin)
			res = max(res, VILLIAGER_VICTORY);
		return res;
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
            if(lov != -1 && !config -> user[lov].death)
			{
				config -> user[lov].death = true;
				broadcastInfo((info + transNumToString(lov)).c_str());
			}
		}
		if(num == config -> sheriffNum)
		{
			broadcastInfo("changeSheriff");
			transferInfoToClient(num, "startVote");
			string info = respond(num, 20000);
			if(info[0] != '!')
				config -> sheriffNum = transCharToNum(info[5]);
			else
				config -> sheriffNum = -1;
			string info2("determineSheriff/");
            broadcastInfo((info2 + transNumToString(config -> sheriffNum)).c_str());
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
					if(canBeVoted(transCharToNum(resp[5])))
						tmp[transCharToNum(resp[5])]++;
                    qDebug() << "sfaaf" << transCharToNum(resp[5]);
					voting[i] = transCharToNum(resp[5]);
                    if(voteInterval() != 0 && i == config -> sheriffNum && canBeVoted(transCharToNum(resp[5])))//只是为了简单判断是不是狼人投票
						tmp[transCharToNum(resp[5])] += 0.5;
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
		{
			broadcastInfo("draw");
			result = ifDraw();
		}
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
        if(!sel.size())
            return -1;
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
								transferInfoToClient(k,(config -> user[i].messeges[j].toStdString() + '/' + transNumToString(i)).c_str());
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
	bool SheriffVote :: canVote(int num)
	{
		return canVoting[num];
	}
	bool SheriffVote :: canBeVoted(int num)
	{
		return isCandidate[num];
	}
	void SheriffVote :: show()
	{
        qDebug() << "show";
        for(int i = 0; i < config -> playerNum; i++)
			if(isCandidate[i])
			{
				vector<int> tmp;
                GotMessege gotMessege(config);
                tmp = gotMessege.gotMessege(i, false, true);
				for(vector<int> :: iterator it = tmp.begin(); it != tmp.end(); it++)
					isCandidate[*it] = false;
			}
	}
    int SheriffVote :: ifDraw()
	{
		if(isDraw)
			return -1;
		SheriffVote *sv = new SheriffVote;
        for(int i = 0; i < config -> playerNum; i++)
		{
			sv -> isCandidate[i] = 0;
			sv -> canVoting[i] = canVoting[i];
		}
		sv -> isDraw = true;
        for(int i = 0; i < config -> playerNum; i++)
		{
			if(res[i].first != res[0].first)
				break;
			sv -> canVoting[res[i].second] = 1;
		}
		sv -> vote();
        return sv -> result;
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
        vector<string> resp = manyRespond(num, 20000);
        if(resp.size() < 2)
		{
			config -> hasCupid = 0;
			return ;
		}
        vector<int> lovs;
        for(vector<string> :: iterator it = resp.begin(); it != resp.end(); it++)
        {
            string str = *it;
            lovs.push_back(transCharToNum(str[5]));
        }
        Lovers lov(num, lovs[0], lovs[1], twoCompare(config -> user[lovs[0]].characterType,config -> user[lovs[1]].characterType, WEREWOLF, TOWNSFOLK) || twoCompare(config -> user[lovs[0]].characterType,config -> user[lovs[1]].characterType, WEREWOLF, GOD));
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
            transferInfoToClient(num, "startVote");
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
    void Hunter :: processInfo()
    {
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
        transferInfoToClient(num, "idiotKilledByVoting");
	}
	void Savior :: init()
	{
		lastSavee = -1;
		config -> lastSavee = -1;
	}
	void Savior :: nightTransferInfo()//6
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
	void Scapegoat :: killedByVoting()
	{
        if(config -> loseAbility)
        {
            transferInfoToClient(num, "roleActLoseAbility");
            return;
        }
        transferInfoToClient(num, "canDetermine");
		transferInfoToClient(num, "startVote");
        for(int i = 0; i < config -> playerNum; i++)
            config -> user[i].canVote = false;
        vector<string> infos = manyRespond(num, 30000);
        for(int i = 0; i < infos.size(); i++)
        {
            string resp = infos[i], info("showVoteResult/");
            config -> user[transCharToNum(resp[5])].canVote = true;
            broadcastInfo((info +  transNumToString(num) + '/' + transNumToString(transCharToNum(resp[5]))).c_str());
        }
    }
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
	void Witch :: nightTransferInfo()//9
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
            if(resp[5] != '0')
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
	void PiedPiper :: nightTransferInfo()
	{
		transferInfoToClient(num, "roleAct");
		transferInfoToClient(num, "startVote");
		string info("hasPuzzled/");
        for(int i = 0; i < config -> playerNum; i++)
			if(config -> user[i].isPuzzled)
                transferInfoToClient(num, (info + transNumToString(num)).c_str());
		
	}
	void PiedPiper :: processInfo()
	{
		vector<string> infos= manyRespond(num, 0);
		for(int i = 0; i < infos.size(); i++)
		{
			string resp = infos[i];
			config -> user[transCharToNum(resp[5])].isPuzzled = true;
		}
	}
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
        config -> user.erase(config -> user.end() - 1);
        config -> user.erase(config -> user.end() - 1);
        string c("changeRole/");
		transferInfoToClient(num, (c + characterName[config -> user[num].characterNum]).c_str());
		if(config -> user[num].characterNum == 3)
			config -> hasCupid = true;
        config -> user[num].characterType = transNumToCharacterType(config -> user[num].characterNum);
		config -> characterNumber[config -> user[num].characterNum].push_back(num);
	}
    void HasSheriffSelection :: selection()
	{
        SheriffVote sheriffVote(config);
		sheriffVote.isDraw = false;
		for(int i = 0; i < config -> playerNum; i++)
		{
            sheriffVote.isCandidate.push_back(0);
            sheriffVote.canVoting.push_back(0);
		}
		broadcastInfo("chooseSheriff");
		bool flag = false;
		string str, info("showSheriffCandidate/");
		for(int i = 0; i < config -> playerNum; i++)
		{
			if(!flag)
			{
				str = respond(i, 20000);
				flag = true;
			}
			else
				str = respond(i, 0);
			if(str[0] == 'y')
			{
				broadcastInfo((info + transNumToString(i)).c_str());
				sheriffVote.isCandidate[i] = 1;
			}
			else
				sheriffVote.canVoting[i] = 1;
		}
        qDebug() << "votevoet";
		sheriffVote.vote();
		config -> sheriffNum = sheriffVote.result;
		string info2("determineSheriff/");
		broadcastInfo((info2 + transNumToString(config -> sheriffNum)).c_str());
	}
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
		/*broadcastInfo("getInfo");
		for(vector<User> :: iterator it = config -> user.begin(); (it + config -> hasThief) != config -> user.end(); it++)
		{
			while(config -> hasConn[it -> num] && config -> user[it -> num].messeges.empty()) ;
			if(config -> hasConn[it -> num])
			{
				QString info = config -> user[it -> num].messeges[0], info2 = QString :: fromStdString(transNumToString(it -> num));
                QString info3("info");
                info = info3 + info + '/' + info2;
				QByteArray ba;
				ba = info.toLatin1();
				char *mm = ba.data();
				broadcastInfo(mm);
			}
		}*/
	}
	vector<int> GotMessege :: gotMessege(int num, bool islastword, bool isSheriffVote)
	{
		vector<int> res;
        if(!config -> hasConn[num])
			return res;
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
		string info("setTime/");
        broadcastInfo((info + transNumToString(19)).c_str());
        QString Qinfo2 = QString::fromStdString(info2);
		QByteArray ba;
		clock_t cl = clock();
		while(clock() - cl < 20100)
		{
			if(!config -> user[num].messeges.empty())
			{
                for(vector<QString> :: iterator it = config -> user[num].messeges.begin(); it != config -> user[num].messeges.end(); it++)
				{
                    qDebug() << *it;
                    QString Qinfo = Qinfo2 + (*it);
					ba = Qinfo.toLatin1();  
					char* mm = ba.data();
					broadcastInfo(mm);
				}
				config -> user[num].messeges.clear();
			}
			if(isSheriffVote)
				for(int i = 0; i < config -> playerNum; i++)
					if(i != num && !config -> user[i].messeges.empty())
					{
						config -> user[i].messeges.clear();
						string str("quit");
						broadcastInfo((str + transNumToString(i)).c_str());
						res.push_back(i);
					}
		}
        transferInfoToClient(num, "stopChat");
		cl = clock();
		while(clock() - cl < 1000) ;
		return res;
    }
	void Wake :: wake()
	{
		vector<int> puzzledPlayers;
        for(int i = 0; i < config -> playerNum; i++)
			if(!config -> user[i].death && config -> user[i].isPuzzled)
				puzzledPlayers.push_back(i);
		for(vector<int> :: iterator it2 = puzzledPlayers.begin(); it2 != puzzledPlayers.end(); it2++)
		{
			string info2("puzzled/");
			broadcastInfo("setTime/10");
			for(vector<int> :: iterator it3 = puzzledPlayers.begin(); it3 != puzzledPlayers.end(); it3++)
				transferInfoToClient(*it2, (info2 + transNumToString(*it3)).c_str());
		}
		clock_t cl = clock();
		while(!puzzledPlayers.empty() && clock() - cl < 10000) ;
	}
	void SheriffChooseOrder :: sheriffChooseOrder(int onedead)
	{
		if(config -> sheriffNum == -1)
        {
            qDebug() << "wwwww";
            for(int i = 0; i < config -> playerNum; i++)
                order.push_back(i);
            qDebug() << "wwwww";
        }
		else
		{
            broadcastInfo("waitingSheriff");
			string str, resp;
			if(onedead == -1)
			{
				str = "sheriff/";
				onedead = config -> sheriffNum;
			}
			else
				str = "deadPlayer/";
			str = str + transNumToString(onedead);
			transferInfoToClient(config -> sheriffNum, str.c_str());
			resp = respond(config -> sheriffNum, 15000);
			str = str + '/' + resp;
			broadcastInfo(str.c_str());
            for(int i = 0; i < config -> playerNum; i++)
			{
				if(resp[0] == 'p')
                    order.push_back((i + onedead + 1) % config -> playerNum);
				else
                    order.push_back((-i + onedead - 1 + config -> playerNum) % config -> playerNum);
			}
		}
	}
	int GameServer :: day(bool isFirstDay)
    {
        qDebug() <<config.deads.size()<<"size"<<endl;
		for(int i = 0 ; i < config.deads.size(); i++)
            if(config.deads[i] != -1)
                character[config.deads[i]] -> killed();
		for(int i = 0 ; i < config.deads.size(); i++)
            if(isFirstDay)
				gotMessege -> gotMessege(config.deads[i], true);
		if(victoryJudge -> judge())
				return victoryJudge -> judge();
		config.deads.clear();
        qDebug()<<"w";
		for(int i = 0 ; i < config.playerNum; i++)
				character[i] -> dayOperation();
        qDebug()<<"w";
		int onedead = -1;
		if(config.deads.size() == 1)
			onedead = config.deads[0];
        qDebug()<<"w";
		if(!config.deads.empty())
		{
			//cout<<config.deads[0]<<endl;
			character[config.deads[0]] -> killed();
			config.deads.clear();
		}
		if(victoryJudge -> judge())
				return victoryJudge -> judge();
        qDebug()<<"ww";
        SheriffChooseOrder sco(&config);
        qDebug()<<"www";
        sco.sheriffChooseOrder(onedead);
        qDebug()<<"w";
		for(int i = 0 ; i < config.playerNum; i++)
			if(!config.user[sco.order[i]].death)
				gotMessege -> gotMessege(sco.order[i], false);
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
		//cout<<"1"<<endl;
		WerewolfOperation w(&config);
		//cout<<"1"<<endl;
		w.operation();
		//cout<<config.killedPlayer <<"kp\n";
		for(vector<Character*> :: iterator it = character.begin(); it != character.end(); it++)
				(*it) -> nightTransferInfo();
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
        Wake wake(&config);
        wake.wake();
	}
	int GameServer :: firstDay()
	{
		broadcast -> broadcast("day");
		for(int i = 0; i < config.playerNum; i++)
			if(!config.user[i].cannotVoteForever)
				config.user[i].canVote = true;
		sheriffSelection -> selection();
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
        //firstNight();
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
        broadcast -> broadcast((info1 + transNumToString(winCode - 1)).c_str());
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
