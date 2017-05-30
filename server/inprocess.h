#ifndef INPROCESS_H
#define INPROCESS_H

#include <QDialog>
#include <QThread>

namespace Ui {
class InProcess;
}

class GameThr : public QThread {
    Q_OBJECT
protected:
    void run();
signals:
    void onGameEnd();
};

class InProcess : public QDialog
{
    Q_OBJECT

public:
    explicit InProcess(QWidget *parent = 0);
    ~InProcess();

    void startGame();

private:
    Ui::InProcess *ui;

    GameThr *thr;

public slots:
    void onGameEnd();
};


#endif // INPROCESS_H
