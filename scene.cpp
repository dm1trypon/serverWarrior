#include "scene.h"

Scene::Scene(const QMap<QString, qreal> position, const QMap<QString, qreal> size, QObject *parent) :
    QObject (parent),
    _position(position),
    _size(size)
{

}

QMap<QString, qreal> Scene::getSize()
{
    return _size;
}

QMap<QString, qreal> Scene::getPosition()
{
    return _position;
}
