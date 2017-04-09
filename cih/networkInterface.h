#pragma once

#include "globalConf.h"

namespace OOPLRS {
namespace net {
    const int broadcastSendPort = 19260;
    const int broadcastRecvPort = 19261;

    class _Connection;
    typedef _Connection *Connection;

    class ServerConn {
        int sendPort, recvPort;
    public :
        typedef struct onRemoteConnectInfo {
            Connection conn;
        } *onRemoteConnectInfo_p;

        typedef void (*onRemoteConnectHandler)(onRemoteConnectInfo_p);

        typedef struct onRemoteDataInfo {
            Connection conn;
            byteseq data;
            size_t len;
        } *onRemoteDataInfo_p;

        typedef void (*onRemoteDataHandler)(onRemoteDataInfo_p);

        ServerConn() 
            : sendPort(broadcastSendPort), recvPort(broadcastRecvPort) { ; }
        ServerConn(int sendPort, int recvPort) 
            : sendPort(sendPort), recvPort(recvPort) { ; } 

        void broadcast(byteseq data, size_t length);

        void beginAcceptConnection();
        void endAcceptConnection();

        void registerOnRemoteConnect(onRemoteConnectHandler handler);
        void unregisterOnRemoteConnect();

        void registerOnRemoteDisconnect(onRemoteConnectHandler handler);
        void unregisterOnRemoteDisconnect();

        bool sendData(Connection conn, byteseq data, size_t length);

        void registerOnRemoteData(onRemoteDataHandler handler);
        void unregisterOnRemoteData();
    };

    class ClientConn {
        int sendPort, recvPort;
    public :
        typedef struct onBroadcastInfo {
            Connection server;
            byteseq data;
            size_t len;
        } onBroadcastInfo_p;

        typedef void (*onBroadcastHandler)(onBroadcastInfo_p);

        typedef struct onServerDataInfo {
            byteseq data;
            size_t len;
        } *onServerDataInfo_p;

        typedef void (*onServerDataHandler)(onServerDataInfo_p);

        ClientConn()
            : sendPort(broadcastSendPort), recvPort(broadcastRecvPort) { ; }
        ClientConn(int sendPort, int recvPort) 
            : sendPort(sendPort), recvPort(recvPort) { ; } 

        void registerOnBroadcastReceived(onBroadcastHandler handler);
        void unregisterOnBroadcastReceived();

        bool connect(Connect server);

        bool sendData(byteseq data, size_t length);

        void registerOnServerData(onServerDataHandler handler);
        void unregisterOnServerData();

        bool disconnect();
    };
}
}

#ifdef XMX_DEBUG
# include "../src/network/networkInterface.cpp"
#endif 