#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "scene.h"

class Collision
{
public:
    Collision();
    QString checkCollisionScene(Player *player, Scene *scene);
    bool checkCollisionPlayers(Player *player, QMap <QString, Player *> players);
};

#endif // COLLISION_H
