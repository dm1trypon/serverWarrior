#include "bullet.h"

Bullet::Bullet(const QMap <QString, qreal> position,
               const QMap <QString, qreal> size,
               const QMap <QString, qreal> click,
               const QString &nickname,
               const int id, QObject *parent) :
    QObject (parent),
    _position(position),
    _size(size),
    _click(click),
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
