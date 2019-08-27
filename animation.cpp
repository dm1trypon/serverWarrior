#include "animation.h"
#include "gameobjects.h"
#include "workjson.h"

#include <QDebug>
#include <QtMath>

Animation::Animation(QObject* parent)
    : QObject(parent)
{
    connect(&_animationTimer, &QTimer::timeout, this, &Animation::process);
}

void Animation::start()
{
    qDebug() << "Start animation...";
    _animationTimer.start(FPS);
}

void Animation::stop()
{
    qDebug() << "Stop animation...";
    _animationTimer.stop();
}

void Animation::process()
{
    const QMap<QString, Player*> players = GameObjects::Instance().getPlayers();

    if (players.isEmpty()) {
        return;
    }

    const QMap<QString, Scene*> scene = GameObjects::Instance().getScene();


    QMap<int, Bullet*> bullets = GameObjects::Instance().getBullets();

    onPlayers(players, scene);
    onBullets(bullets, players, scene);

    if (!_delBullets.isEmpty()) {
        bullets = onDelBullets(bullets);
    }

    WorkJson::Instance().toSend(WorkJson::Instance().toJsonObjects(GameObjects::Instance().getPlayers(), bullets, scene));
}

QMap<int, Bullet*> Animation::onDelBullets(QMap<int, Bullet*> bullets)
{
    QPair<QString, int> delBullet;

    foreach (delBullet, _delBullets) {
        bullets.remove(delBullet.second);

        GameObjects::Instance().delBullets(delBullet.second);
    }

    _delBullets.clear();

    return bullets;
}

void Animation::onBullets(const QMap<int, Bullet*> bullets,
    const QMap<QString, Player*> players,
    const QMap<QString, Scene*> scene)
{
    foreach (Bullet* bullet, bullets) {
        if (!bullet) {
            continue;
        }

        const QMap<QString, qreal> position = bullet->getPosition();
        const QMap<QString, qreal> speedMove = bullet->getSpeedMove();

        QMap<QString, qreal> newPosition;
        newPosition.insert("x", position["x"] + speedMove["speed_x"]);
        newPosition.insert("y", position["y"] + speedMove["speed_y"]);

        bullet->setPosition(newPosition);

        if (!bullet->isAlive()) {
            _delBullets.append(QPair<QString, int>(bullet->getNickname(), bullet->getId()));
            continue;
        }

        if (_collision.checkCollisionBullets(bullet, GameObjects::Instance().getBullets(), players, scene)) {
            if (bullet->getHealth() > 0) {
                return;
            }

            _delBullets.append(QPair<QString, int>(bullet->getNickname(), bullet->getId()));
        }
    }
}

void Animation::onPlayers(const QMap<QString, Player*> players, const QMap<QString, Scene*> scene)
{
    foreach (Player* player, players) {
        playerRotation(player);

        const QString side = _collision.checkCollisionScene(player, scene["scene"]);

        if (side == "left") {
            player->setInertSpeed(QPointF(-1, 1));
        }

        if (side == "right") {
            player->setInertSpeed(QPointF(-1, 1));
        }

        if (side == "top") {
            player->setInertSpeed(QPointF(1, -1));
        }

        if (side == "bottom") {
            player->setInertSpeed(QPointF(1, -1));
        }

        const QMap<QString, qreal> position = player->getPosition();
        const QMap<QString, qreal> speed = player->getSpeed();

        QMap<QString, qreal> newPosition;
        newPosition.insert("x", position["x"] + speed["speed_x"]);
        newPosition.insert("y", position["y"] + speed["speed_y"]);

        player->setPosition(newPosition);

        if (!_collision.checkCollisionPlayers(player, players)) {
            continue;
        }

        player->setInertSpeed(QPointF(-1, -1));
    }
}

void Animation::playerRotation(Player* player)
{
    const QMap<QString, qreal> size = player->getSize();
    const QMap<QString, qreal> position = player->getPosDisplay();

    const QPointF cursor = player->getCursor();

    const qreal cx = position["width"];
    const qreal cy = position["height"];
    const qreal angle = qAtan2(cursor.y() - cy, cursor.x() - cx) * HALF_G / PI;

    if (static_cast<int>(player->getRotate()) == static_cast<int>(angle)) {
        return;
    }

    player->setRotate(angle);
}
