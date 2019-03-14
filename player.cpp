#include "player.h"
#include "gameobjects.h"

#include <QDebug>

Player::Player(const QMap <QString, qreal> position,
               const QMap <QString, qreal> size,
               const QString &nickname,
               const int id, QObject *parent) :
    QObject(parent),
    _position(position),
    _width(size["width"]), _height(size["height"]),
    _maxSpeed(GameObjects::Instance().getSpeedPlayers()),
    _life(GameObjects::Instance().getLifePlayers()),
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

int Player::getShotSpeed()
{
    return _shotSpeed;
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
//    WorkJson::Instance().toSend(WorkJson::Instance().toJsonDie(_nickname));
//    GameObjects::Instance().toPlayers(_nickname, this, REMOVE);
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

void Player::setShotSpeed(const int shotSpeed)
{
    _shotSpeed = shotSpeed;
}

void Player::setMaxSpeed(const qreal maxSpeed)
{
    _maxSpeed = maxSpeed;
}

qreal Player::getMaxSpeed()
{
    return _maxSpeed;
}
