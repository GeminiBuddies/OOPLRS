#include "inprocess.h"
#include "ui_inprocess.h"
#include "over.h"
#include "commvar.h"

#include <QThread>

void GameThr::run() {
    qDebug() << "Game thread is :" << QThread::currentThread();
    temp.endGame(temp.mainProcess());

    emit onGameEnd();
}

InProcess::InProcess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InProcess)
{
    ui->setupUi(this);
}

InProcess::~InProcess()
{
    delete ui;
}

void InProcess::startGame() {
    temp.reshuffle();
    if (temp.config.user[0].conn)
        temp.startGame->startGame();

    thr = new GameThr();
    thr->start();

    QObject::connect(thr, SIGNAL(onGameEnd()), this, SLOT(onGameEnd()));
}

void InProcess::onGameEnd() {
    close();
    qDebug() << "end";
    temp.config.serverConn -> close();
    Over* ov = new Over;
    ov->show();
}
