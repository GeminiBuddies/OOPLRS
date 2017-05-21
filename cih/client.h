#pragma once

#include "globalConf.h"

namespace OOPLRS {
namespace client {
    struct ServerInfo;
    class ServerInfoCollection;

    class ClientConnection {
    public :
        typedef Character* (*onGameStart)(Identity);

        ClientConnection();

        void start(); // 
        ServerInfoCollection getServerList();
        bool Connect(ServerInfo server);
        void Disconnect();

        void registerOnGameStart(onGameStart handler);
    };

    class Character {
    public :
        Character();

        virtual void OnMsg(string json);
    }
}
}