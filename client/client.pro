TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    player.cpp \
    character.cpp \
    mainwindowproxy.cpp \
    mainformproxy.cpp \
    uiproxy.cpp \
    characterimageproxy.cpp \
    chatboxproxy.cpp \
    gamerecorderproxy.cpp \
    mousearea.cpp \
    messager.cpp \
    messagedealer.cpp \
    beforestartmessagedealer.cpp \
    werewolf.cpp \
    townsfolk.cpp \
    seer.cpp \
    witch.cpp \
    savior.cpp \
    scapegoat.cpp \
    ancient.cpp \
    cupid.cpp \
    hunter.cpp \
    idiot.cpp \
    daymessagedealer.cpp \
    nightmessagedealer.cpp \
    timer.cpp \
    serverlist.cpp \
    optionproxy.cpp \
    dead.cpp \
    welcomeformproxy.cpp \
    uimessagedealer.cpp \
    thief.cpp \
    thiefchooseformproxy.cpp \
    witchchooseformproxy.cpp \
    piedpiper.cpp \
    client.cpp \
    clientconn.cpp \
    ..\cih\globalConf.cpp \
    temp.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    player.h \
    character.h \
    mainwindowproxy.h \
    mainformproxy.h \
    uiproxy.h \
    characterimageproxy.h \
    chatboxproxy.h \
    gamerecorderproxy.h \
    mousearea.h \
    messager.h \
    messagedealer.h \
    beforestartmessagedealer.h \
    werewolf.h \
    townsfolk.h \
    seer.h \
    witch.h \
    savior.h \
    scapegoat.h \
    ancient.h \
    cupid.h \
    hunter.h \
    idiot.h \
    daymessagedealer.h \
    nightmessagedealer.h \
    optionproxy.h \
    timerproxy.h \
    serverlistproxy.h \
    dead.h \
    welcomeformproxy.h \
    uimessagedealer.h \
    thief.h \
    thiefchooseformproxy.h \
    witchchooseformproxy.h \
    piedpiper.h \
    client.h \
    clientconn.h \
    ..\cih\globalConf.h \
    temp.h
