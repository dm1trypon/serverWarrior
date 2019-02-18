#include "collision.h"

Collision::Collision()
{

}

QString Collision::checkCollision(Player *player, Scene *scene)
{
    const QMap <QString, qreal> sizePlayer = player->getSize();
    const QMap <QString, qreal> sizeScene = scene->getSize();

    const QMap <QString, qreal> positionPlayer = player->getPosition();
    const QMap <QString, qreal> positionScene = scene->getPosition();

    if (positionPlayer["x"] < positionScene["x"])
    {
        return "left";
    }

    if (positionPlayer["x"] + sizePlayer["width"] > positionScene["x"] + sizeScene["width"])
    {
        return "right";
    }

    if (positionPlayer["y"] < positionScene["y"])
    {
        return "top";
    }

    if (positionPlayer["y"] + sizePlayer["height"] > positionScene["y"] + sizeScene["height"])
    {
        return "bottom";
    }

    return "inside";
}

bool Collision::checkCollisionPlayers(Player *player, QMap <QString, Player *> players)
{
    const QMap <QString, qreal> sizePlayer = player->getSize();
    const QMap <QString, qreal> positionPlayer = player->getPosition();

    foreach (Player *enemyPlayer, players)
    {
        if (player->getNickname() != enemyPlayer->getNickname())
        {
            const QMap <QString, qreal> positionEnemyPlayer = enemyPlayer->getPosition();
            const qreal distWidth = positionEnemyPlayer["x"] + 2 * sizePlayer["width"] - positionPlayer["x"];
            const qreal distHeight = positionEnemyPlayer["y"] + 2 * sizePlayer["width"] - positionPlayer["y"];
            const qreal distance = sqrt(distWidth * distWidth + distHeight + distHeight);

            if (distance < sizePlayer["width"])
            {
                return true;
            }
        }
    }

    return false;
}
