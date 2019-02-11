#include "animation.h"

Animation::Animation(QObject *parent) :
    QObject(parent)
{
    connect(&_animationTimer, &QTimer::timeout, this, &Animation::process);
}

void Animation::start()
{
    _animationTimer.start(FPS);
}

void Animation::stop()
{
    _animationTimer.stop();
}

void Animation::process()
{
    _objects
}

void Animation::setObjects(QMap <QString, Player *> objects)
{
    _objects = objects;
}
