#include "gameobjects.h"
#include <ctime>

#include <QDebug>

GameObjects::GameObjects(QObject *parent) :
    QObject(parent)
{
    srand(static_cast<uint>(time(nullptr)));
}

GameObjects &GameObjects::Instance()
{
    static GameObjects theSingleInstance;
    return theSingleInstance;
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

void GameObjects::toPlayers(QString nickname, Player *player, bool operation)
{
    if (operation)
    {
        qDebug() << "Add player" << nickname << "to player's list...";
        _players.insert(nickname, player);
        return;
    }

    qDebug() << "Remove player" << nickname << "from player's list...";
    _players.remove(nickname);
    qDebug() << _players;
}

int GameObjects::generateId()
{
    return qrand() % (999999 - 100000) + 100000;
}

QMap <QString, qreal> GameObjects::generateXY()
{
    QMap <QString, qreal> posXY;
    posXY.insert("x", qrand() % (1000 - 1) + 1);
    posXY.insert("y", qrand() % (1000 - 1) + 1);
    return posXY;
}

void GameObjects::controlPlayers(QString nickname, QString key, bool isHold)
{
    QMap <QString, qreal> speedPlayer;

    if (key == "up")
    {
        speedPlayer.insert("speedX", 0);
        speedPlayer.insert("speedY", -speed);
    }

    if (key == "down")
    {
        speedPlayer.insert("speedX", 0);
        speedPlayer.insert("speedY", speed);
    }

    if (key == "left")
    {
        speedPlayer.insert("speedX", -speed);
        speedPlayer.insert("speedY", 0);
    }

    if (key == "right")
    {
        speedPlayer.insert("speedX", speed);
        speedPlayer.insert("speedY", 0);
    }

    if (isKeyboardSticking(nickname, speedPlayer, isHold))
    {
        qWarning() << "Warning! Sticking keybord, check client!";
        return;
    }

    _players[nickname]->setSpeed(speedPlayer);
    _players[nickname]->setMove(isHold);
}

bool GameObjects::isKeyboardSticking(QString nickname, QMap <QString, qreal> speedPlayer, bool isHold)
{
    return _players[nickname]->getSpeed() == speedPlayer && _players[nickname]->getMove() == isHold;
}

QMap <QString, Player *> GameObjects::getPlayers()
{
    return _players;
}

void GameObjects::clearList()
{
    qDeleteAll(_players.begin(), _players.end());
    _players.clear();
}
