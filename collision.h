#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "bullet.h"
#include "scene.h"

class Collision
{
public:
    Collision();
    QString checkCollisionScene(Player *player, Scene *scene);
    bool checkCollisionPlayers(Player *player, const QMap <QString, Player *> players);
    bool checkCollisionBullets(Bullet *bullet, const QMap<int, Bullet *> bullets, const QMap <QString, Player *> players, const QMap <QString, Scene *> scene);
private:
    bool isBulletSceneCollision(const QMap<QString, qreal> positionBullet, const QMap<QString, qreal> positionScene, const QMap<QString, qreal> sizeBullet, const QMap<QString, qreal> sizeScene);
};

#endif // COLLISION_H
