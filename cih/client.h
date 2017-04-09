#pragma once

#include "globalConf.h"

namespace OOPLRS {
namespace client {
    struct ServerInfo;
    class ServerInfoCollection;

    class ClientConnection {
    public :
        typedef void (*onGameStart)();

        ClientConnection();

        void start();
        ServerInfoCollection getServerList();
        bool Connect(ServerInfo server);
        void Disconnect();

        void registerOnGameStart(onGameStart handler);
    };

    class Character {
    public :
        Character();

        template <typename Arg>
        void forward(Arg arg);

        template <typename Arg>
        void registerBackward(void (*handler)(Arg));
    }
}
}