#pragma once

#include "globalConf.h"

namespace OOPLRS {
namespace server {
    struct GameConfig;
    class GameEvent;
    typedef class GameEvent GameEvent_p;

    class GameServer {
    public :
        typedef void (*EventHandler)(GameEvent_p);

        GameServer(GameConfig conf);

        void runServer();
        void registerEventHandler(EventHandler handler);
        void unregisterEventHandler();
    };
}
}