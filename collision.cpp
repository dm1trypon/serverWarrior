#include "collision.h"

#include <QtMath>
#include <QDebug>

Collision::Collision()
{

}

QString Collision::checkCollisionScene(Player *player, Scene *scene)
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

    QMap <QString, qreal> positionPlayer = player->getPosition();
    positionPlayer["x"] = positionPlayer["x"] + sizePlayer["width"] / 2;
    positionPlayer["y"] = positionPlayer["y"] + sizePlayer["height"] / 2;

    foreach (Player *enemyPlayer, players)
    {
        if (player->getNickname() != enemyPlayer->getNickname())
        {
            QMap <QString, qreal> positionEnemyPlayer = enemyPlayer->getPosition();
            positionEnemyPlayer["x"] = positionEnemyPlayer["x"] + sizePlayer["width"] / 2;
            positionEnemyPlayer["y"] = positionEnemyPlayer["y"] + sizePlayer["height"] / 2;

            const qreal distWidth = positionEnemyPlayer["x"] - positionPlayer["x"];
            const qreal distHeight = positionEnemyPlayer["y"] - positionPlayer["y"];
            const qreal distance = qAbs(sqrt(distWidth * distWidth + distHeight * distHeight));


            if (distance < sizePlayer["width"])
            {
                qDebug() << positionPlayer << positionEnemyPlayer << distance << distWidth << distHeight;
                return true;
            }
        }
    }

    return false;
}
