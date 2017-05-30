#ifndef CONNECT_H
#define CONNECT_H

#include <QDialog>
#include<vector>
#include<iostream>

using namespace std;



namespace Ui {
class Connect;
}

class Connect : public QDialog
{
    Q_OBJECT

public:
    explicit Connect(QWidget *parent = 0);
    ~Connect();
    void showConnect(int* player,int a);

private slots:
    void on_start_clicked();

    void on_cancel_clicked();

private:
    Ui::Connect *ui;
};

#endif // CONNECT_H
