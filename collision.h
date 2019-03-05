#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "bullet.h"
#include "scene.h"

class Collision
{
private:
    struct CollisionObjects
    {
        QString &playerNick;
        QString &enemyNick;
        QMap <QString, qreal> playerPos;
        QMap <QString, qreal> enemyPos;
        qreal playerSize;
        qreal enemySize;
    };

    bool isCollisionObjects(CollisionObjects *_collisionObjects);
    QString onCollisionScene(const QMap <QString, qreal> positionBullet, const QMap <QString, Scene *> scene, const qreal sizeObject);
public:
    Collision();
    QString checkCollisionScene(Player *player, const QMap<QString, Scene *> scene);
    bool checkCollisionPlayers(Player *player, const QMap <QString, Player *> players);
    bool checkCollisionBullets(Bullet *bullet, const QMap <int, Bullet *> bullets, const QMap <QString, Player *> players, const QMap <QString, Scene *> scene);
};

#endif // COLLISION_H
