#include "gameobjects.h"

#include <QDebug>

GameObjects::GameObjects(QObject *parent) :
    QObject(parent)
{

}

bool GameObjects::isExistPlayer(QString nickname)
{
    if (players.contains(nickname))
    {
        qDebug() << "Player" << nickname << "is exist!";
        return true;
    }

    qDebug() << "Player" << nickname << "is not exist!";
    return false;
}

void GameObjects::toPlayers(QString nickname, QObject *player)
{
    qDebug() << "Add player" << nickname << "to player's list...";
    players.insert(nickname, player);
}

int GameObjects::generateId()
{
    return qrand() % (999999 - 100000) + 100000;
}
