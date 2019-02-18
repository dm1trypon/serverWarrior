#include "player.h"

Player::Player(const QMap <QString, qreal> position,
               const QMap <QString, qreal> speed,
               const QMap <QString, qreal> size,
               const QString &nickname,
               const int id, QObject *parent) :
    QObject(parent),
    _width(size["width"]), _height(size["height"]),
    _posX(position["x"]), _posY(position["y"]),
    _speedX(speed["speed_x"]), _speedY(speed["speed_y"]),
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

QMap <QString, qreal> Player::getOldPosition()
{
    QMap <QString, qreal> oldPosition;
    oldPosition.insert("x", _posXold);
    oldPosition.insert("y", _posYold);
    return oldPosition;
}

void Player::setOldPosition(const QMap <QString, qreal> oldPosition)
{
    _posXold = oldPosition["x"];
    _posYold = oldPosition["y"];
}

QMap <QString, qreal> Player::getSize()
{
    QMap <QString, qreal> size;
    size.insert("width", _width);
    size.insert("height", _height);
    return size;
}

QMap <QString, qreal> Player::getSpeed()
{
    QMap <QString, qreal> speed;
    speed.insert("speed_x", _speedX);
    speed.insert("speed_y", _speedY);
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

void Player::setSpeed(const QMap <QString, qreal> speed)
{
    _speedX = speed["speed_x"];
    _speedY = speed["speed_y"];
}

void Player::setPosition(const QMap <QString, qreal> position)
{
    QMap <QString, qreal> oldPosition;
    oldPosition.insert("x", _posX);
    oldPosition.insert("y", _posY);

    setOldPosition(oldPosition);

    _posX = position["x"];
    _posY = position["y"];
}

void Player::setMove(bool isHold)
{
    _move = isHold;
}
