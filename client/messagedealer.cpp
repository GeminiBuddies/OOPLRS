#include "messagedealer.h"

MessageDealer::MessageDealer(Messager* player){
    this->player=player;
    QObject::connect(this, SIGNAL(sendMessage(QString,QString,QString,QString,QString)),player,SLOT(receiveMessage(QString,QString,QString,QString,QString)));

}
