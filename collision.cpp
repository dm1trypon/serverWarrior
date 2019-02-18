#include "collision.h"

Collision::Collision()
{

}

QString Collision::checkCollision(Player *player, Scene *scene)
{
    QMap <QString, qreal> sizePlayer = player->getSize();
    QMap <QString, qreal> sizeScene = scene->getSize();

    QMap <QString, qreal> positionPlayer = player->getPosition();
    QMap <QString, qreal> positionScene = scene->getPosition();

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
