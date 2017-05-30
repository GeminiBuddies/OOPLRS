#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include<QString>
#include<player.h>
#include"uiproxy.h"
#include"mainwindowproxy.h"
#include"mainformproxy.h"
#include"chatboxproxy.h"
#include"gamerecorderproxy.h"
#include"characterimageproxy.h"
#include"mousearea.h"
#include "timerproxy.h"
#include "serverlistproxy.h"
#include "optionproxy.h"
#include "welcomeformproxy.h"
#include "thiefchooseformproxy.h"
#include "witchchooseformproxy.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qRegisterMetaType<byteseq>("byteseq");
    qRegisterMetaType<Conn>("Conn");
    
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    //确定根对象mainWindow，赋值给root
    QObject* root=NULL;
    QList<QObject*> rootObjects=engine.rootObjects();
    int count=rootObjects.size();
    for(int i=0;i<count;i++){
        if(rootObjects.at(i)->objectName()=="mainWindow"){
            root=rootObjects.at(i);
            break;
        }
    }

    //建立c++与qml的联系
    Player* player=new Player;

    player->ui=new MainWindowProxy(0,player);
    player->ui->setItem(root);
    player->ui->connectSignal();
    player->ui->setName("mainWindowProxy");

    UiProxy* mainFormProxy=player->ui->addChild<MainFormProxy>("mainFormProxy",player);
    mainFormProxy->setItem("mainForm");
    mainFormProxy->connectSignal();

    UiProxy* thiefChooseFormProxy=mainFormProxy->addChild<ThiefChooseFormProxy>("thiefChooseFormProxy",player);
    thiefChooseFormProxy->setItem("thiefChooseForm");
    thiefChooseFormProxy->connectSignal();

    UiProxy* witchChooseFormProxy=mainFormProxy->addChild<WitchChooseFormProxy>("witchChooseFormProxy",player);
    witchChooseFormProxy->setItem("witchChooseForm");
    witchChooseFormProxy->connectSignal();

    UiProxy* welcomeFormProxy=player->ui->addChild<WelcomeFormProxy>("welcomeFormProxy",player);
    welcomeFormProxy->setItem("welcomeForm");
    welcomeFormProxy->connectSignal();

    UiProxy* timerProxy=mainFormProxy->addChild<TimerProxy>("timer",player);
    timerProxy->setItem("timer");
    timerProxy->connectSignal();

    UiProxy* chatBoxProxy=mainFormProxy->addChild<ChatBoxProxy>("chatBoxProxy",player);
    chatBoxProxy->setItem("universeDialog1");
    chatBoxProxy->connectSignal();

    UiProxy* gameRecorderProxy=mainFormProxy->addChild<GameRecorderProxy>("gameRecorderProxy",player);
    gameRecorderProxy->setItem("gameRecorder1");
    gameRecorderProxy->connectSignal();

    UiProxy* serverListProxy=player->ui->addChild<ServerListProxy>("serverListProxy",player);
    serverListProxy->setItem("serverList");
    serverListProxy->connectSignal();

    UiProxy* optionProxy=player->ui->addChild<OptionProxy>("optionProxy",player);
    optionProxy->setItem("option");
    optionProxy->connectSignal();

    for(int i=1;i<=20;i++){
        QVariant t=i;
        QString temp="characterImage"+t.toString();

        mainFormProxy->addChild<CharacterImageProxy>(temp,player);
        mainFormProxy->children[temp]->setItem(temp);
        mainFormProxy->children[temp]->connectSignal();

        mainFormProxy->children[temp]->addChild<MouseArea>("mouseArea",player);
        mainFormProxy->children[temp]->children["mouseArea"]->setItem("mouseArea1");
        mainFormProxy->children[temp]->children["mouseArea"]->connectSignal();
    }







    return app.exec();
}
