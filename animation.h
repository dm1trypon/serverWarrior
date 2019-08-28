#ifndef ANIMATION_H
#define ANIMATION_H

#include "collision.h"

#include <QObject>
#include <QTimer>
#include <QMap>

class Player;
class Bullet;
class Wall;

class Animation : public QObject
{
    Q_OBJECT

public:
    Animation(QObject *parent = nullptr);
    void start();
    void stop();

private slots:
    void process();
    void onGenerateWall();

private:
    const int FPS = 17;
    const int HALF_G = 180;
    const qreal PI = 3.14;

    Collision _collision;
    QTimer _animationTimer;
    QTimer _generateWall;
    QList<QPair<QString, int> > _delBullets;

    void onPlayers(const QMap <QString, Player *> players, const QMap <QString, Scene *> scene);
    void onBullets(const QMap <int, Bullet *> bullets, const QMap <QString, Player *> players,
                   const QMap<int, Wall *> walls,
                   const QMap <QString, Scene *> scene);

    void playerRotation(Player *player);
    QMap<int, Bullet *> onDelBullets(QMap<int, Bullet *> bullets);
};

#endif // ANIMATION_H
