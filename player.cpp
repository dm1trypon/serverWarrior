#include "player.h"

Player::Player(QMap <QString, qreal> position, qreal speedX, qreal speedY, QString nickname, int id, QObject *parent) :
    QObject(parent),
    _posX(position["x"]), _posY(position["y"]),
    _speedX(speedX), _speedY(speedY),
    _id(id),
    _nickname(nickname)
{

}

QString Player::getNickname()
{
    return _nickname;
}

QMap <QString, qreal> Player::getPosition()
{
    QMap <QString, qreal> position;
    position.insert("x", _posX);
    position.insert("y", _posY);
    return position;
}

QMap <QString, qreal> Player::getSpeed()
{
    QMap <QString, qreal> speed;
    speed.insert("speedX", _speedX);
    speed.insert("speedY", _speedY);
    return speed;
}

int Player::getIdPlayer()
{
    return _id;
}

bool Player::getMove()
{
    return _move;
}

void Player::setSpeed(QMap <QString, qreal> speed)
{
    _speedX = speed["speedX"];
    _speedY = speed["speedY"];
}

void Player::setPosition(QMap <QString, qreal> position)
{
    _posX = position["x"];
    _posY = position["y"];
}

void Player::setMove(bool isHold)
{
    _move = isHold;
}
