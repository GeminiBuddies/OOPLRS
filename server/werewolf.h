#ifndef WEREWOLF_H
#define WEREWOLF_H

#include <QDialog>

namespace Ui {
class Werewolf;
}

class Werewolf : public QDialog
{
    Q_OBJECT

public:
    explicit Werewolf(QWidget *parent = 0);
    ~Werewolf();

private:
    Ui::Werewolf *ui;
};

#endif // WEREWOLF_H
