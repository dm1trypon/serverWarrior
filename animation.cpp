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
    QMap <QString, Player *> players = GameObjects::Instance().getPlayers();
    QMap <QString, Scene *> scene = GameObjects::Instance().getScene();

    foreach (Player *player, players)
    {
        const QString side = _collision.checkCollision(player, scene["scene"]);

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

        if (_collision.checkCollisionPlayers(player, players))
        {
            QMap <QString, qreal> position;
            position.insert("x", player->getOldPosition()["x"] + player->getSpeed()["speed_x"] + horizontal);
            position.insert("y", player->getOldPosition()["y"] + player->getSpeed()["speed_y"] + vertical);
            player->setPosition(position);

            break;
        }

        QMap <QString, qreal> position;
        position.insert("x", player->getPosition()["x"] + player->getSpeed()["speed_x"] + horizontal);
        position.insert("y", player->getPosition()["y"] + player->getSpeed()["speed_y"] + vertical);
        player->setPosition(position);


    }

    WorkJson::Instance().toSend(WorkJson::Instance().toJsonObjects(players, scene));
}
