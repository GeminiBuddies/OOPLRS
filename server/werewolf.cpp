#include "werewolf.h"
#include "ui_werewolf.h"

Werewolf::Werewolf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Werewolf)
{
    ui->setupUi(this);
    setWindowTitle(QString(u8"狼人杀"));

}

Werewolf::~Werewolf()
{
    delete ui;
}

