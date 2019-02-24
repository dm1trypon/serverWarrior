#include "gameobjects.h"
#include <ctime>

#include <QDebug>
#include <QtMath>

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

void GameObjects::setSizeScene(const QMap <QString, int> sizeScene)
{
    _sizeScene = sizeScene;
}

void GameObjects::setBulletSpeed(Bullet *bullet)
{
    qDebug() << bullet->getClick();

    const qreal speedX = ((bullet->getClick()["x"] - _players[bullet->getNickname()]->getPosition()["x"])
            * bullet->getSpeed()
            / sqrt(qPow(bullet->getClick()["x"] - _players[bullet->getNickname()]->getPosition()["x"], 2)
            + qPow(bullet->getClick()["y"] - _players[bullet->getNickname()]->getPosition()["y"], 2)));

    const qreal speedY = ((bullet->getClick()["y"] - _players[bullet->getNickname()]->getPosition()["y"])
            * bullet->getSpeed()
            / sqrt(qPow(bullet->getClick()["x"] - _players[bullet->getNickname()]->getPosition()["x"], 2)
            + qPow(bullet->getClick()["y"] - _players[bullet->getNickname()]->getPosition()["y"], 2)));

    QMap <QString, qreal> speed;
    speed.insert("speed_x", speedX);
    speed.insert("speed_y", speedY);

    bullet->setSpeedMove(speed);
}

void GameObjects::createScene()
{
    QMap <QString, qreal> position;
    position.insert("x", 0);
    position.insert("y", 0);

    QMap <QString, qreal> size;
    size.insert("width", _sizeScene["width"]);
    size.insert("height", _sizeScene["height"]);

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

void GameObjects::toBullets(const int id, Bullet *bullet)
{
    _bullets.insert(id, bullet);
    setBulletSpeed(bullet);
}

void GameObjects::delBullets(const QString &nickname, const int id)
{
    _bullets.remove(id);
    WorkJson::Instance().toSend( WorkJson::Instance().toJsonRemove(nickname, id));
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

qreal GameObjects::getSpeedPlayers()
{
    return speed;
}

QMap <int, Bullet *> GameObjects::getBullets()
{
    return _bullets;
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
