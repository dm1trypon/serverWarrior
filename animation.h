#ifndef ANIMATION_H
#define ANIMATION_H

#include "player.h"

#include <QObject>
#include <QTimer>
#include <QMap>

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

    QTimer _animationTimer;
};

#endif // ANIMATION_H
