#include "wall.h"

Wall::Wall(const QMap<QString, qreal> position, const QMap<QString, qreal> size, const int id, QObject *parent) :
    QObject (parent),
    _position(position),
    _size(size),
    _id(id)
{

}

QMap<QString, qreal> Wall::getSize()
{
    return _size;
}

QMap<QString, qreal> Wall::getPosition()
{
    return _position;
}

int Wall::getHealth()
{
    return _health;
}

int Wall::getId()
{
    return _id;
}

int Wall::getDamage()
{
    return DAMAGE;
}

void Wall::setHealth(const int damage)
{
    _health = _health - damage;
}
