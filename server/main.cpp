#include "mainwindow.h"
#include <QApplication>
#include"werewolf.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Werewolf asd;
    if(asd.exec()==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else return 0;






}
