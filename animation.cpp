#include "animation.h"
#include "gameobjects.h"
#include "workjson.h"

#include <QDebug>
#include <QtMath>

Animation::Animation(QObject* parent)
    : QObject(parent)
{
    qDebug() << "Animation has been created.";
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
    const QMap<QString, Scene*> scene = GameObjects::Instance().getScene();
    const QMap<int, Bullet*> bullets = GameObjects::Instance().getBullets();

    onPlayers(GameObjects::Instance().getPlayers(), scene);

    onBullets(bullets,
        GameObjects::Instance().getPlayers(),
        scene);

    WorkJson::Instance().toSend(WorkJson::Instance().toJsonObjects(GameObjects::Instance().getPlayers(),
        bullets,
        scene));

    if (_delBullets.isEmpty()) {
        return;
    }

    onDelBullets();

}

void Animation::onDelBullets()
{
    QPair<QString, int> delBullet;

    foreach (delBullet, _delBullets) {
        GameObjects::Instance().delBullets(delBullet.first, delBullet.second);
    }

    _delBullets.clear();
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
            return;
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

        qreal vertical = 0;
        qreal horizontal = 0;

        if (side == "inside") {
        }

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

        if (_collision.checkCollisionPlayers(player, players)) {
            QMap<QString, qreal> newPosition;
            newPosition.insert("x", position["x"] - speed["speed_x"] + horizontal);
            newPosition.insert("y", position["y"] - speed["speed_y"] + vertical);
            player->setPosition(newPosition);
        }
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
