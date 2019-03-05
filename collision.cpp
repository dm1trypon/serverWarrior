#include "collision.h"

#include <QtMath>
#include <QDebug>

Collision::Collision()
{

}

QString Collision::checkCollisionScene(Player *player, const QMap <QString, Scene *> scene)
{
    const qreal sizePlayer = player->getSize()["width"];
    const QMap <QString, qreal> positionPlayer = player->getPosition();

    return onCollisionScene(positionPlayer, scene, sizePlayer);
}

bool Collision::checkCollisionPlayers(Player *player, const QMap <QString, Player *> players)
{
    CollisionObjects *collisionObjects = nullptr;
    collisionObjects->playerNick = player->getNickname();
    collisionObjects->playerSize = player->getSize()["width"] / 2;
    collisionObjects->playerPos = player->getPosition();

    collisionObjects->playerPos["x"] = collisionObjects->playerPos["x"] + collisionObjects->playerSize;
    collisionObjects->playerPos["y"] = collisionObjects->playerPos["y"] + collisionObjects->playerSize;

    foreach (Player *enemyPlayer, players)
    {
        collisionObjects->enemyNick = enemyPlayer->getNickname();
        collisionObjects->enemySize = enemyPlayer->getSize()["width"];
        collisionObjects->enemyPos = enemyPlayer->getPosition();

        if (isCollisionObjects(collisionObjects))
        {
            enemyPlayer->setLife(enemyPlayer->getLife() - 1);
            memset(&collisionObjects, 0, sizeof(CollisionObjects));

            return isCollisionObjects(collisionObjects);
        }
    }

    memset(&collisionObjects, 0, sizeof(CollisionObjects));

    return false;
}

bool Collision::checkCollisionBullets(Bullet *bullet,
                                      const QMap <int, Bullet *> bullets,
                                      const QMap <QString, Player *> players,
                                      const QMap <QString, Scene *> scene)
{
    bool collision = false;

    CollisionObjects *collisionObjects = nullptr;
    collisionObjects->playerNick = bullet->getNickname();
    collisionObjects->playerSize = bullet->getSize()["width"] / 2;
    collisionObjects->playerPos = bullet->getPosition();

    collisionObjects->playerPos["x"] = collisionObjects->playerPos["x"] + collisionObjects->playerSize;
    collisionObjects->playerPos["y"] = collisionObjects->playerPos["y"] + collisionObjects->playerSize;

    foreach (Player *enemyPlayer, players)
    {
        collisionObjects->enemyNick = enemyPlayer->getNickname();
        collisionObjects->enemySize = enemyPlayer->getSize()["width"];
        collisionObjects->enemyPos = enemyPlayer->getPosition();

        if (isCollisionObjects(collisionObjects))
        {
            collision = true;
            enemyPlayer->setLife(enemyPlayer->getLife() - 1);
            break;
        }
    }

    foreach (Bullet *enemyPlayer, bullets)
    {
        collisionObjects->enemyNick = enemyPlayer->getNickname();
        collisionObjects->enemySize = enemyPlayer->getSize()["width"];
        collisionObjects->enemyPos = enemyPlayer->getPosition();

        if (isCollisionObjects(collisionObjects))
        {
            collision = true;
            break;
        }
    }

    collision = !onCollisionScene(collisionObjects->playerPos, scene, collisionObjects->playerSize).contains("inside");

    memset(&collisionObjects, 0, sizeof(CollisionObjects));

    if (collision)
    {
        return true;
    }

    return false;
}

QString Collision::onCollisionScene(const QMap <QString, qreal> positionBullet,
                                 const QMap <QString, Scene *> scene,
                                 const qreal sizeObject)
{
    const QMap <QString, qreal> positionScene = scene["scene"]->getPosition();
    const QMap <QString, qreal> sizeScene = scene["scene"]->getSize();

    if (positionBullet["x"] < positionScene["x"])
    {
         return "left";
    }

    if (positionBullet["x"] + sizeObject > positionScene["x"] + sizeScene["width"])
    {
        return "right";
    }

    if (positionBullet["y"] < positionScene["y"])
    {
        return "top";
    }

    if (positionBullet["y"] + sizeObject > positionScene["y"] + sizeScene["height"])
    {
        return "bottom";
    }

    return "inside";
}

bool Collision::isCollisionObjects(CollisionObjects *collisionObjects)
{
    if (collisionObjects->playerNick == collisionObjects->enemyNick)
    {
        return false;
    }

    collisionObjects->enemyPos["x"] = collisionObjects->enemyPos["x"] + collisionObjects->enemySize;
    collisionObjects->enemyPos["y"] = collisionObjects->enemyPos["y"] + collisionObjects->enemySize;

    const qreal distWidth = collisionObjects->enemyPos["x"] - collisionObjects->playerPos["x"];
    const qreal distHeight = collisionObjects->enemyPos["y"] - collisionObjects->playerPos["y"];
    const qreal distance = qAbs(sqrt(distWidth * distWidth + distHeight * distHeight));

    if (distance < collisionObjects->playerSize + collisionObjects->enemySize)
    {
        return true;
    }

    return false;

}
