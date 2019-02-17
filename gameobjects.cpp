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

void GameObjects::createScene()
{
    QMap <QString, qreal> position;
    position.insert("x", 0);
    position.insert("y", 0);

    QMap <QString, qreal> size;
    size.insert("width", 3840);
    size.insert("height", 2160);

    _scene.insert("scene", new Scene(position, size));
}

bool GameObjects::isExistPlayer(const QString &nickname)
{
    if (_players.contains(nickname))
    {
        qDebug() << "Player" << nickname << "is exist!";
        return true;
    }

    qDebug() << "Player" << nickname << "is not exist!";
    return false;
}

void GameObjects::toPlayers(const QString &nickname, Player *player, const bool operation)
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

void GameObjects::controlPlayers(const QString &nickname, const QString &key, const bool isHold)
{
    qDebug() << nickname << key << isHold;
    QMap <QString, qreal> speedPlayer;

    if (key == "up")
    {
        speedPlayer.insert("speed_x", 0);
        speedPlayer.insert("speed_y", -speed);
    }

    if (key == "down")
    {
        speedPlayer.insert("speed_x", 0);
        speedPlayer.insert("speed_y", speed);
    }

    if (key == "left")
    {
        speedPlayer.insert("speed_x", -speed);
        speedPlayer.insert("speed_y", 0);
    }

    if (key == "right")
    {
        speedPlayer.insert("speed_x", speed);
        speedPlayer.insert("speed_y", 0);
    }

    if (isKeyboardSticking(nickname, speedPlayer, isHold))
    {
        qWarning() << "Warning! Sticking keybord, check client!";
        return;
    }

    if (!isHold)
    {
        speedPlayer.insert("speed_x", 0);
        speedPlayer.insert("speed_y", 0);
    }

    _players[nickname]->setSpeed(speedPlayer);
    _players[nickname]->setMove(isHold);
}

bool GameObjects::isKeyboardSticking(const QString &nickname, const QMap <QString, qreal> speedPlayer, const bool isHold)
{
    return _players[nickname]->getSpeed() == speedPlayer && _players[nickname]->getMove() == isHold;
}

QMap <QString, Player *> GameObjects::getPlayers()
{
    return _players;
}

QMap <QString, Scene *> GameObjects::getScene()
{
    return _scene;
}

void GameObjects::clearList()
{
    qDeleteAll(_players.begin(), _players.end());
    _players.clear();
}
