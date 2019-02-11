#include "gameobjects.h"

#include <QDebug>

GameObjects::GameObjects(QObject *parent) :
    QObject(parent)
{
    srand(static_cast<uint>(time(nullptr)));
}

bool GameObjects::isExistPlayer(QString nickname)
{
    if (_players.contains(nickname))
    {
        qDebug() << "Player" << nickname << "is exist!";
        return true;
    }

    qDebug() << "Player" << nickname << "is not exist!";
    return false;
}

void GameObjects::toPlayers(QString nickname, QObject *player, bool operation)
{
    if (operation)
    {
        qDebug() << "Add player" << nickname << "to player's list...";
        _players.insert(nickname, player);
        return;
    }

    qDebug() << "Remove player" << nickname << "from player's list...";
    _players.remove(nickname);
}

int GameObjects::generateId()
{
    return qrand() % (999999 - 100000) + 100000;
}

QMap <QString, qreal> GameObjects::generateXY()
{
    QMap <QString, qreal> posXY;
    posXY.insert("X", qrand() % (1000 - 1) + 1);
    posXY.insert("Y", qrand() % (1000 - 1) + 1);
    return posXY;
}

QMap <QString, QObject *> GameObjects::getPlayers()
{
    return _players;
}
