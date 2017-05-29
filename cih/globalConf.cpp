#ifndef GLOBAL_CONF_CPP
#define GLOBAL_CONF_CPP 1

#include "globalConf.h"

QString GetName(Conn c) {
    return c->name;
}

QHostAddress getBroadcastAddr() {
    for (auto i : QNetworkInterface::allInterfaces()) {
        auto flg = i.flags();
        if (! CONTAIN(flg, QNetworkInterface::IsUp | QNetworkInterface::IsRunning | QNetworkInterface::CanBroadcast)) continue;
        if (CONTAIN(flg, QNetworkInterface::IsLoopBack) || CONTAIN(flg, QNetworkInterface::IsPointToPoint)) continue;

        if (i.humanReadableName().indexOf(QString("Virtual")) != -1) continue;

        for (auto a : i.addressEntries()) {
            if (a.ip().toString().length() >= 16) continue;
            if (a.prefixLength() < 0) continue;

            return a.broadcast();
        }
    }

    return QHostAddress(QString("192.168.1.255"));
}

LRSBasicLayerFrame::LRSBasicLayerFrame() : type(frameType::Data), data(QByteArray("")) { }

LRSBasicLayerFrame::LRSBasicLayerFrame(frameType type, QByteArray data) : type(type), data(data) { ; }

LRSBasicLayerFrame LRSBasicLayerFrame::FromQByteArray(QByteArray arr) {
    LRSBasicLayerFrame rv((LRSBasicLayerFrame::frameType)(char)arr[0], arr.mid(1, arr.length() - 1));
    return rv;
}

QByteArray LRSBasicLayerFrame::ToQByteArray() {
    auto rv = QByteArray();

    rv.append((char)(int)type);
    rv.append(data);

    return rv;
}

#endif
