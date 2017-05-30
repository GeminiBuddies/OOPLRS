#include "mainwindow.h"
#include <QApplication>
#include"werewolf.h"

#include "../cih/globalConf.h"
#include <QtCore>

int main(int argc, char *argv[])
{
    qRegisterMetaType<byteseq>("byteseq");
    qRegisterMetaType<Conn>("Conn");

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
