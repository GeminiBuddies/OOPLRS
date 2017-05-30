#include "connect.h"
#include "ui_connect.h"
#include "record.h"
#include <vector>
#include <iostream>
#include "mainwindow.h"
#include "commvar.h"
#include "over.h"
#include "inprocess.h"


using namespace std;


Connect::Connect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connect)
{
    ui->setupUi(this);
    void showConnect(int* player,int a);
}

Connect::~Connect()
{
    delete ui;
}

void Connect::on_start_clicked()
{
    temp.config.serverConn->endAcceptConnection();

    close();
    InProcess *v = new InProcess;
    v->startGame();
    v->show();
}

void Connect::onClientChanged() {
    showConnect(temp.config.hasConn, temp.config.playerNum);

    if (temp.config.playerNum > temp.config.connNum) {
        ui->start->setEnabled(false);
    } else {
        ui->start->setEnabled(true);
    }
}

void Connect::showConnect(bool* player,int a)
{
    ui->textBrowser->setPlainText("");

    ui->textBrowser->append(tr("Connecting..."));


    for(int i=0;i<a;i++)
    {
        if(!player[i])
        {
            ui->textBrowser->append("player");
            ui->textBrowser->moveCursor(QTextCursor::End);
            ui->textBrowser->insertPlainText(QString::number(i+1,10));
            ui->textBrowser->moveCursor(QTextCursor::End);
            ui->textBrowser->insertPlainText(" hasn't connected");
        }
        else
        {
            ui->textBrowser->append("player");
            ui->textBrowser->moveCursor(QTextCursor::End);
            ui->textBrowser->insertPlainText(QString::number(i+1,10));
            ui->textBrowser->moveCursor(QTextCursor::End);
            ui->textBrowser->insertPlainText(" has connected");
        }
    }


}

void Connect::on_cancel_clicked()
{
    temp.config.serverConn->endAcceptConnection();

    close();
    MainWindow *m = new MainWindow;
    m->show();
}
