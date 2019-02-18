#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "scene.h"

class Collision
{
public:
    Collision();
    QString checkCollision(Player *player, Scene *scene);
};

#endif // COLLISION_H
