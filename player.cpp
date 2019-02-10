#include "player.h"

Player::Player(qreal posX, qreal posY, qreal speedX, qreal speedY, QString nickname, int id, QObject *parent) :
    QObject(parent),
    _posX(posX), _posY(posY),
    _speedX(speedX), _speedY(speedY),
    _id(id),
    _nickname(nickname)
{

}
