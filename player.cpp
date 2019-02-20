#include "player.h"
#include "gameobjects.h"

#include <QDebug>

Player::Player(const QMap <QString, qreal> position,
               const QMap <QString, qreal> speed,
               const QMap <QString, qreal> size,
               const QString &nickname,
               const int id, QObject *parent) :
    QObject(parent),
    _width(size["width"]), _height(size["height"]),
    _posX(position["x"]), _posY(position["y"]),
    _speedX(speed["speed_x"]), _speedY(speed["speed_y"]),
    _maxSpeed(GameObjects::Instance().getSpeedPlayers()),
    _id(id),
    _nickname(nickname)
{
    connect(&_speedTimer, &QTimer::timeout, this, &Player::setSpeed);
    const int timeSpeed = 100;
    _speedTimer.start(timeSpeed);
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

void Player::setMaxSpeed(const QMap <QString, qreal> speed)
{
    _maxSpeedX = speed["speed_x"];
    _maxSpeedY = speed["speed_y"];
}

void Player::setSpeed()
{
    if (_maxSpeedX > 0.0 && _speedX < _maxSpeed)
    {
        _speedX ++;
    }

    if (_maxSpeedX < 0.0 && _speedX > -_maxSpeed)
    {
        _speedX --;
    }

    if (_maxSpeedY > 0.0 && _speedY < _maxSpeed)
    {
        _speedY ++;
    }

    if (_maxSpeedY < 0.0 && _speedY > -_maxSpeed)
    {
        _speedY --;
    }

    if (_maxSpeedX == 0.0 && _speedX > -_maxSpeedX)
    {
        _speedX --;
    }

    if (_maxSpeedX == 0.0 && _speedX < _maxSpeedX)
    {
        _speedX ++;
    }

    if (_maxSpeedY == 0.0 && _speedY > -_maxSpeedY)
    {
        _speedY --;
    }

    if (_maxSpeedY == 0.0 && _speedY < _maxSpeedY)
    {
        _speedY ++;
    }
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
