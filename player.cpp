#include "player.h"

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
    _id(id),
    _nickname(nickname)
{
    connect(&_speedTimer, &QTimer::timeout, this, &Player::setSlowSpeed);
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
    if (speed["speed_x"] == 0.0)
    {
        if (_speedTimer.isActive())
        {
            _speedTimer.stop();
        }

        if (_speedX < 0.0)
        {
            _side = "left";
            _speedCoefX = _speedX;
            _speedCoefY = _speedY;
            _speedTimer.start();
        }

        if (_speedX > 0.0)
        {
            _side = "right";
            _speedCoefX = _speedX;
            _speedCoefY = _speedY;
            _speedTimer.start();
        }

        _speedY = speed["speed_y"];

        return;
    }

    if (speed["speed_y"] == 0.0)
    {
        if (_speedTimer.isActive())
        {
            _speedTimer.stop();
        }

        if (_speedY < 0.0)
        {
            _side = "up";
            _speedCoefX = _speedX;
            _speedCoefY = _speedY;
            _speedTimer.start();
        }

        if (_speedY > 0.0)
        {
            _side = "down";
            _speedCoefX = _speedX;
            _speedCoefY = _speedY;
            _speedTimer.start();
        }

        _speedX = speed["speed_x"];

        return;
    }
}

void Player::setSlowSpeed()
{
    if (_side == "left")
    {
        _speedCoefX ++;
        _speedX = _speedCoefX;
    }

    if (_side == "right")
    {
        _speedCoefX --;
        _speedX = _speedCoefX;
    }

    if (_side == "up")
    {
        _speedCoefY ++;
        _speedY = _speedCoefY;
    }

    if (_side == "down")
    {
        _speedCoefY --;
        _speedY = _speedCoefY;
    }

    if (_speedCoefX == 0.0)
    {
        _speedTimer.stop();
    }

    if (_speedCoefY == 0.0)
    {
        _speedTimer.stop();
    }
}

//void Player::setSpeed(const QMap <QString, qreal> speed)
//{
//    if (static_cast<int>(speed["speed_x"]) == 0 && static_cast<int>(speed["speed_y"]) == 0)
//    {
//        qDebug() << _speedX << _speedY;

//        if (_speedTimer.isActive())
//        {
//            _speedTimer.stop();
//        }

//        if (_speedX != 0.0)
//        {
//            _speedCoef = _speedX;
//        }

//        if (_speedY != 0.0)
//        {
//            _speedCoef = _speedY;
//        }

//        qDebug() << _speedX << _speedY;

//        _speedTimer.start(100);
//        return;
//    }

//    if (_speedTimer.isActive())
//    {
//        _speedTimer.stop();
//    }

//    _speedX = speed["speed_x"];
//    _speedY = speed["speed_y"];
//}

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
