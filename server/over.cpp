#include "over.h"
#include "ui_over.h"

Over::Over(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Over)
{
    ui->setupUi(this);
}

Over::~Over()
{
    delete ui;
}

void Over::on_pushButton_clicked()
{
    close();
}
