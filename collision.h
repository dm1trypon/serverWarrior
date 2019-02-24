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
    bool checkCollisionBullets(Bullet *bullet, const QMap <QString, Player *> players, const QMap <QString, Scene *> scene);
};

#endif // COLLISION_H
