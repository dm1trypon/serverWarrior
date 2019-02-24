#ifndef ANIMATION_H
#define ANIMATION_H

#include "collision.h"

#include <QObject>
#include <QTimer>
#include <QMap>

class Player;
class Bullet;

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
    void onPlayers(const QMap <QString, Player *> players, const QMap <QString, Scene *> scene);
    void onBullets(const QMap <int, Bullet *> bullets, const QMap <QString, Player *> players, const QMap <QString, Scene *> scene);
};

#endif // ANIMATION_H
