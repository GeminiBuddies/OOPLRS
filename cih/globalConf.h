#ifndef GLOBAL_CONF
#define GLOBAL_CONF 1

#include <QtCore>
#include <QtNetwork>
#include <QByteArray>
#include <QNetworkInterface>

const int ServerBroadcastInterval = 4; // 4 sec
const int ServerBroadcastRecvInterval = 4000;
const int ServerBroadcastSendPort = 38775;
const int ServerBroadcastRecvPort = 38776;
const int ServerClientPort = 38777;
const int MaxPlayer = 32;
const int NetInterval = 200; // 200 ms
const int ConnectPackageTimeOut = 3000; // 3000 ms

#define CONTAIN(v, flg) (((v) & (flg)) == (flg))

typedef const char *byteseq;

class _Conn;
typedef const _Conn *Conn;

class _Conn {
public:
    QString name;
    QHostAddress addr;

    int id;
};

QString GetName(Conn c);

QHostAddress getBroadcastAddr();

class LRSBasicLayerFrame {
protected:
    LRSBasicLayerFrame();

public:
    enum class frameType {
        Broadcast,
        Connect,
        Disconnect,
        Data,
    };

    LRSBasicLayerFrame(frameType type, QByteArray data);

    frameType type;
    QByteArray data;

    static LRSBasicLayerFrame FromQByteArray(QByteArray arr);
    QByteArray ToQByteArray();
};

#endif
