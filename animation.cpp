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
    qDebug() << "Tic-Tak";
    QMap <QString, Player *> players = GameObjects::Instance().getPlayers();

    foreach (Player *player, players)
    {
        QMap <QString, qreal> position;
        position.insert("X", player->getPosition()["X"] + player->getSpeed()["speedX"]);
        position.insert("Y", player->getPosition()["Y"] + player->getSpeed()["speedY"]);
        player->setPosition(position);
    }

    WorkJson::Instance().toSend(WorkJson::Instance().toJsonPlayers(players));
}
