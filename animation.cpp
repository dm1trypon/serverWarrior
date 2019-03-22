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
    QMap<QString, Scene*> scene = GameObjects::Instance().getScene();

    onPlayers(GameObjects::Instance().getPlayers(), scene);

    onBullets(GameObjects::Instance().getBullets(),
        GameObjects::Instance().getPlayers(),
        scene);

    WorkJson::Instance().toSend(WorkJson::Instance().toJsonObjects(GameObjects::Instance().getPlayers(),
        GameObjects::Instance().getBullets(),
        scene));
}

void Animation::onBullets(const QMap<int, Bullet*> bullets,
    const QMap<QString, Player*> players,
    const QMap<QString, Scene*> scene)
{
    foreach (Bullet* bullet, bullets) {
        const QMap<QString, qreal> position = bullet->getPosition();
        const QMap<QString, qreal> speedMove = bullet->getSpeedMove();

        QMap<QString, qreal> newPosition;
        newPosition.insert("x", position["x"] + speedMove["speed_x"]);
        newPosition.insert("y", position["y"] + speedMove["speed_y"]);

        bullet->setPosition(newPosition);

        if (!bullet->isAlive()) {
            GameObjects::Instance().delBullets(bullet->getNickname(), bullet->getId());
        }

        if (_collision.checkCollisionBullets(bullet, bullets, players, scene)) {
            GameObjects::Instance().delBullets(bullet->getNickname(), bullet->getId());
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
            horizontal = 10;
        }

        if (side == "right") {
            horizontal = -10;
        }

        if (side == "top") {
            vertical = 10;
        }

        if (side == "bottom") {
            vertical = -10;
        }

        const QMap<QString, qreal> position = player->getPosition();
        const QMap<QString, qreal> speed = player->getSpeed();

        QMap<QString, qreal> newPosition;
        newPosition.insert("x", position["x"] + speed["speed_x"] + horizontal);
        newPosition.insert("y", position["y"] + speed["speed_y"] + vertical);

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

    QPointF cursor = player->getCursor();

    const qreal cx = position["width"] + size["width"] / 2;
    const qreal cy = position["height"] + size["height"] / 2;
    const qreal angle = qAtan2(cursor.y() - cy, cursor.x() - cx) * HALF_G / PI;

    if (static_cast<int>(player->getRotate()) == static_cast<int>(angle)) {
        return;
    }

    player->setRotate(angle);
}
