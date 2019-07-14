#include "player.h"
#include "gameobjects.h"

#include <QDebug>

Player::Player(const QMap <QString, qreal> position,
               const QMap <QString, qreal> posDisplay,
               const QMap <QString, qreal> size,
               const QString &nickname,
               const int id, QObject *parent) :
    QObject(parent),
    _position(position),
    _posDisplay(posDisplay),
    _width(size["width"]), _height(size["height"]),
    _maxSpeed(GameObjects::Instance().getSpeedPlayers()),
    _life(GameObjects::Instance().getLifePlayers()),
    _id(id),
    _nickname(nickname)
{
    connect(&_speedTimer, &QTimer::timeout, this, &Player::inertialBraking);
    const int timeSpeed = 100;
    _speedTimer.start(timeSpeed);
}

QString Player::getNickname()
{
    return _nickname;
}

const QMap <QString, qreal> Player::getPosDisplay()
{
    return _posDisplay;
}

void Player::setShot()
{
    if (!_isShot)
    {
        _isShot = true;
        return;
    }

    _isShot = false;
}

QTimer *Player::getShotTimer()
{
    return _shotTimer;
}

bool Player::getShot()
{
    return _isShot;
}

QMap <QString, qreal> Player::getPosition()
{
    return _position;
}

QMap <QString, qreal> Player::getSize()
{
    QMap <QString, qreal> size;
    size.insert("width", _width);
    size.insert("height", _height);
    return size;
}

void Player::setRotate(const qreal rotate)
{
    _rotate = rotate;
}

qreal Player::getRotate()
{
    return _rotate;
}

QMap <QString, qreal> Player::getSpeed()
{
    QMap <QString, qreal> speed;
    speed.insert("speed_x", _speedX);
    speed.insert("speed_y", _speedY);
    return speed;
}

int Player::getId()
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

void Player::setInertSpeed(const QPointF coef)
{
    _speedX = _speedX * coef.x();
    _speedY = _speedY * coef.y();
}

void Player::inertialBraking()
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

int Player::getLife()
{
    return _life;
}

void Player::resetLife()
{
    _life = GameObjects::Instance().getLifePlayers();
}

void Player::onDamage(const int damage)
{
    _life = _life - damage;

    if (_life > 0)
    {
        return;
    }

    _position = GameObjects::Instance().generateXY();
}

void Player::setCursor(const QPointF cursor)
{
    _cursor = cursor;
}

QPointF Player::getCursor()
{
    return _cursor;
}

int Player::getScore()
{
    return _score;
}

void Player::setScore()
{
    _score ++;
}

void Player::setPosition(const QMap <QString, qreal> position)
{
    _position["x"] = position["x"];
    _position["y"] = position["y"];
}

void Player::setMove(const bool isHold)
{
    _move = isHold;
}

qreal Player::getMaxSpeed()
{
    return _maxSpeed;
}
