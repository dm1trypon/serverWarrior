#ifndef ANIMATION_H
#define ANIMATION_H

#include "collision.h"

#include <QObject>
#include <QTimer>
#include <QMap>

class Player;

class Animation : public QObject
{
    Q_OBJECT

public:
    Animation(QObject *parent = nullptr);
    void start();
    void stop();

private slots:
    void process();

private:
    const int FPS = 10;

    Collision _collision;
    QTimer _animationTimer;
};

#endif // ANIMATION_H
