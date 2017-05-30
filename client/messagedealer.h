#ifndef MESSAGEDEALER_H
#define MESSAGEDEALER_H

#include "messager.h"
#include "uiproxy.h"

class MessageDealer : public Messager
{
    Q_OBJECT
public:
    MessageDealer(Messager* player);

protected:
    Messager* player;

signals:

};

#endif // MESSAGEDEALER_H
