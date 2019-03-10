#include "bullet.h"
#include "gameobjects.h"

Bullet::Bullet(const QMap <QString, qreal> position,
               const QMap <QString, qreal> size,
               const QMap <QString, qreal> click,
               const QString &nickname,
               const int id, QObject *parent) :
    QObject (parent),
    _speed(GameObjects::Instance().getSpeedBullets()),
    _position(position),
    _click(click),
    _size(size),
    _nickname(nickname),
    _id(id)
{

}

void Bullet::setPosition(const QMap <QString, qreal> position)
{
    _position = position;
}

void Bullet::setSpeedMove(const QMap <QString, qreal> speedMove)
{
    _speedMove = speedMove;
}

void Bullet::setSpeed(const qreal speed)
{
    _speed = speed;
}

QMap <QString, qreal> Bullet::getSpeedMove()
{
    return _speedMove;
}

QString Bullet::getNickname()
{
    return _nickname;
}

qreal Bullet::getSpeed()
{
    return _speed;
}

int Bullet::getDamage()
{
    return _damage;
}

void Bullet::setDamage(const int damage)
{
    _damage = damage;
}

int Bullet::getId()
{
    return _id;
}

QMap <QString, qreal> Bullet::getPosition()
{
    return _position;
}

QMap <QString, qreal> Bullet::getClick()
{
    return _click;
}

QMap <QString, qreal> Bullet::getSize()
{
    return _size;
}
