#include "animation.h"
#include "gameobjects.h"
#include "workjson.h"

#include <QDebug>

Animation::Animation(QObject *parent) :
    QObject(parent)
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
    QMap <QString, Scene *> scene = GameObjects::Instance().getScene();

    onPlayers(GameObjects::Instance().getPlayers(), scene);
    onBullets(GameObjects::Instance().getBullets(), GameObjects::Instance().getPlayers(), scene);

    WorkJson::Instance().toSend(WorkJson::Instance().toJsonObjects(GameObjects::Instance().getPlayers(), GameObjects::Instance().getBullets(), scene));
}

void Animation::onBullets(const QMap <int, Bullet *> bullets, const QMap <QString, Player *> players, const QMap <QString, Scene *> scene)
{
    foreach (Bullet *bullet, bullets)
    {
        QMap <QString, qreal> position = bullet->getPosition();
        QMap <QString, qreal> speedMove = bullet->getSpeedMove();

        QMap <QString, qreal> newPosition;
        newPosition.insert("x", position["x"] + speedMove["speed_x"]);
        newPosition.insert("y", position["y"] + speedMove["speed_y"]);

        bullet->setPosition(newPosition);

        if (_collision.checkCollisionBullets(bullet, bullets, players, scene))
        {
            GameObjects::Instance().delBullets(bullet->getNickname(), bullet->getId());
        }
    }
}

void Animation::onPlayers(const QMap <QString, Player *> players, const QMap <QString, Scene *> scene)
{
    foreach (Player *player, players)
    {
        const QString side = _collision.checkCollisionScene(player, scene);

        qreal vertical = 0;
        qreal horizontal = 0;

        if (side == "inside")
        {

        }

        if (side == "left")
        {
            horizontal = 10;
        }

        if (side == "right")
        {
            horizontal = -10;
        }

        if (side == "top")
        {
            vertical = 10;
        }

        if (side == "bottom")
        {
            vertical = -10;
        }

        QMap <QString, qreal> position = player->getPosition();
        QMap <QString, qreal> speed = player->getSpeed();

        QMap <QString, qreal> newPosition;
        newPosition.insert("x", position["x"] + speed["speed_x"] + horizontal);
        newPosition.insert("y", position["y"] + speed["speed_y"] + vertical);
        player->setPosition(newPosition);

        if (_collision.checkCollisionPlayers(player, players))
        {
            QMap <QString, qreal> newPosition;
            newPosition.insert("x", position["x"] - speed["speed_x"] + horizontal);
            newPosition.insert("y", position["y"] - speed["speed_y"] + vertical);
            player->setPosition(newPosition);
        }
    }
}
