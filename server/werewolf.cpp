#include "werewolf.h"
#include "ui_werewolf.h"

Werewolf::Werewolf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Werewolf)
{
    ui->setupUi(this);
}

Werewolf::~Werewolf()
{
    delete ui;
}
