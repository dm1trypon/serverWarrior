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

    if (positionPlayer["x"] < positionScene["x"]) {
        return "left";
    }

    if (positionPlayer["x"] + sizePlayer["width"] > positionScene["x"] + sizeScene["width"]) {
        return "right";
    }

    if (positionPlayer["y"] < positionScene["y"]) {
        return "top";
    }

    if (positionPlayer["y"] + sizePlayer["height"] > positionScene["y"] + sizeScene["height"]) {
        return "bottom";
    }

    return "inside";
}

bool Collision::checkCollisionPlayers(Player *player, const QMap <QString, Player *> players)
{
    const QMap <QString, qreal> sizePlayer = player->getSize();

    QMap <QString, qreal> positionPlayer = player->getPosition();
    positionPlayer["x"] = positionPlayer["x"] + sizePlayer["width"] / 4;
    positionPlayer["y"] = positionPlayer["y"] + sizePlayer["height"] / 4;

    foreach (Player *enemyPlayer, players) {
        if (player->getNickname() == enemyPlayer->getNickname()) {
            continue;
        }

        QMap <QString, qreal> positionEnemyPlayer = enemyPlayer->getPosition();
        positionEnemyPlayer["x"] = positionEnemyPlayer["x"] + sizePlayer["width"] / 4;
        positionEnemyPlayer["y"] = positionEnemyPlayer["y"] + sizePlayer["height"] / 4;

        const qreal distWidth = positionEnemyPlayer["x"] - positionPlayer["x"];
        const qreal distHeight = positionEnemyPlayer["y"] - positionPlayer["y"];
        const qreal distance = qAbs(sqrt(distWidth * distWidth + distHeight * distHeight));

        if (distance < sizePlayer["width"]) {
            return true;
        }
    }

    return false;
}

bool Collision::checkCollisionBullets(Bullet *bullet,
                                      const QMap <int, Bullet *> bullets,
                                      const QMap <QString, Player *> players,
                                      const QMap <QString, Scene *> scene)
{
    const QMap <QString, qreal> sizeBullet = bullet->getSize();

    bool collision = false;

    QMap <QString, qreal> positionBullet = bullet->getPosition();
    positionBullet["x"] = positionBullet["x"] + sizeBullet["width"] / 4;
    positionBullet["y"] = positionBullet["y"] + sizeBullet["height"] / 4;

    foreach (Player *enemyPlayer, players)
    {
        const QString nicknameBullet = bullet->getNickname();

        if (nicknameBullet == enemyPlayer->getNickname()) {
            continue;
        }

        QMap <QString, qreal> positionEnemyPlayer = enemyPlayer->getPosition();

        const QMap <QString, qreal> sizeEnemyPlayer = enemyPlayer->getSize();

        positionEnemyPlayer["x"] = positionEnemyPlayer["x"] + sizeEnemyPlayer["width"] / 4;
        positionEnemyPlayer["y"] = positionEnemyPlayer["y"] + sizeEnemyPlayer["height"] / 4;

        const qreal distWidth = positionEnemyPlayer["x"] - positionBullet["x"];
        const qreal distHeight = positionEnemyPlayer["y"] - positionBullet["y"];
        const qreal distance = qAbs(sqrt(distWidth * distWidth + distHeight * distHeight));

        if (distance < sizeBullet["width"] / 4 + sizeEnemyPlayer["width"] / 4) {
            bullet->setHealth(bullet->getHealth());

            collision = true;
            enemyPlayer->onDamage(bullet->getDamage());

            if (enemyPlayer->getLife() <= 0) {
                enemyPlayer->resetLife();

                if (!players.contains(nicknameBullet)) {
                    break;
                }

                players[nicknameBullet]->setScore();
            }

            break;
        }
    }

    foreach (Bullet *enemyBullet, bullets) {
        if (!enemyBullet) {
            continue;
        }

        if (bullet->getNickname() == enemyBullet->getNickname()) {
            continue;
        }

        QMap <QString, qreal> positionEnemyBullet = enemyBullet->getPosition();
        positionEnemyBullet["x"] = positionEnemyBullet["x"] + sizeBullet["width"] / 4;
        positionEnemyBullet["y"] = positionEnemyBullet["y"] + sizeBullet["height"] / 4;

        const qreal distWidth = positionEnemyBullet["x"] - positionBullet["x"];
        const qreal distHeight = positionEnemyBullet["y"] - positionBullet["y"];
        const qreal distance = qAbs(sqrt(distWidth * distWidth + distHeight * distHeight));

        if (distance < sizeBullet["width"]) {
            enemyBullet->setHealth(bullet->getDamage());
            bullet->setHealth(enemyBullet->getDamage());

            collision = true;
            break;
        }
    }

    const QMap <QString, qreal> positionScene = scene["scene"]->getPosition();
    const QMap <QString, qreal> sizeScene = scene["scene"]->getSize();

    if (isBulletSceneCollision(positionBullet, positionScene, sizeBullet, sizeScene)) {
        bullet->setHealth(bullet->getHealth());

        collision = true;
    }

    if (collision) {
        return true;
    }

    return false;
}

bool Collision::isBulletSceneCollision(const QMap <QString, qreal> positionBullet,
                                       const QMap <QString, qreal> positionScene,
                                       const QMap <QString, qreal> sizeBullet,
                                       const QMap <QString, qreal> sizeScene)
{
    return positionBullet["x"] < positionScene["x"]
            || positionBullet["x"] + sizeBullet["width"] / 4 > positionScene["x"] + sizeScene["width"]
            || positionBullet["y"] < positionScene["y"]
            || positionBullet["y"] + sizeBullet["height"] / 4 > positionScene["y"] + sizeScene["height"];
}
