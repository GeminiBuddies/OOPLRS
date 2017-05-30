#ifndef OVER_H
#define OVER_H

#include <QDialog>

namespace Ui {
class Over;
}

class Over : public QDialog
{
    Q_OBJECT

public:
    explicit Over(QWidget *parent = 0);
    ~Over();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Over *ui;
};

#endif // OVER_H
