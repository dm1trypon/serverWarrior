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

bool Collision::checkCollisionPlayers(Player *player, const QMap <QString, Player *> players)
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

bool Collision::checkCollisionBullets(Bullet *bullet, const QMap <int, Bullet *> bullets, const QMap <QString, Player *> players, const QMap <QString, Scene *> scene)
{
    const QMap <QString, qreal> sizeBullet = bullet->getSize();

    bool collision = false;

    QMap <QString, qreal> positionBullet = bullet->getPosition();
    positionBullet["x"] = positionBullet["x"] + sizeBullet["width"] / 2;
    positionBullet["y"] = positionBullet["y"] + sizeBullet["height"] / 2;

    foreach (Player *enemyPlayer, players)
    {
        if (bullet->getNickname() != enemyPlayer->getNickname())
        {
            QMap <QString, qreal> positionEnemyPlayer = enemyPlayer->getPosition();
            const QMap <QString, qreal> sizeEnemyPlayer = enemyPlayer->getSize();
            positionEnemyPlayer["x"] = positionEnemyPlayer["x"] + sizeEnemyPlayer["width"] / 2;
            positionEnemyPlayer["y"] = positionEnemyPlayer["y"] + sizeEnemyPlayer["height"] / 2;

            const qreal distWidth = positionEnemyPlayer["x"] - positionBullet["x"];
            const qreal distHeight = positionEnemyPlayer["y"] - positionBullet["y"];
            const qreal distance = qAbs(sqrt(distWidth * distWidth + distHeight * distHeight));

            if (distance < sizeBullet["width"] / 2 + sizeEnemyPlayer["width"] / 2)
            {
                collision = true;
                enemyPlayer->setLife();

                if (!players.contains(enemyPlayer->getNickname()))
                {
                    players[bullet->getNickname()]->setScore();
                }

                break;
            }
        }
    }

    foreach (Bullet *enemyBullet, bullets)
    {
        if (bullet->getNickname() != enemyBullet->getNickname())
        {
            QMap <QString, qreal> positionEnemyBullet = enemyBullet->getPosition();
            positionEnemyBullet["x"] = positionEnemyBullet["x"] + sizeBullet["width"] / 2;
            positionEnemyBullet["y"] = positionEnemyBullet["y"] + sizeBullet["height"] / 2;

            const qreal distWidth = positionEnemyBullet["x"] - positionBullet["x"];
            const qreal distHeight = positionEnemyBullet["y"] - positionBullet["y"];
            const qreal distance = qAbs(sqrt(distWidth * distWidth + distHeight * distHeight));

            if (distance < sizeBullet["width"])
            {
                collision = true;
                break;
            }
        }
    }

    const QMap <QString, qreal> positionScene = scene["scene"]->getPosition();
    const QMap <QString, qreal> sizeScene = scene["scene"]->getSize();

    if (positionBullet["x"] < positionScene["x"])
    {
        collision = true;
    }

    if (positionBullet["x"] + sizeBullet["width"] > positionScene["x"] + sizeScene["width"])
    {
        collision = true;
    }

    if (positionBullet["y"] < positionScene["y"])
    {
        collision = true;
    }

    if (positionBullet["y"] + sizeBullet["height"] > positionScene["y"] + sizeScene["height"])
    {
        collision = true;
    }

    if (collision)
    {
        return true;
    }

    return false;
}
