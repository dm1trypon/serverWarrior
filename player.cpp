#include "player.h"

Player::Player(QMap <QString, qreal> position, qreal speedX, qreal speedY, QString nickname, int id, QObject *parent) :
    QObject(parent),
    _posX(position["X"]), _posY(position["Y"]),
    _speedX(speedX), _speedY(speedY),
    _id(id),
    _nickname(nickname)
{

}

QString Player::getNickname()
{
    return _nickname;
}

void Player::setPosition(qreal speedX, qreal speedY)
{
    _posX = _posX + speedX;
    _posY = _posY + speedY;
}

void Player::setMove(bool isHold)
{
    _move = isHold;
}
