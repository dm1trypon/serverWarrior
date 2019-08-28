#include "gameobjects.h"
#include <ctime>

#include <QDebug>
#include <QtMath>

GameObjects::GameObjects(QObject* parent)
    : QObject(parent)
{
    srand(static_cast<uint>(time(nullptr)));
}

GameObjects& GameObjects::Instance()
{
    static GameObjects theSingleInstance;
    return theSingleInstance;
}

void GameObjects::setSizeScene(const QMap<QString, int> sizeScene)
{
    _sizeScene = sizeScene;
}

void GameObjects::setSpeedMove(Bullet* bullet)
{
    const QString nickname = bullet->getNickname();
    const QMap<QString, qreal> click = bullet->getClick();
    const QMap<QString, qreal> size = _players[nickname]->getSize();

    QMap<QString, qreal> position = _players[nickname]->getPosition();
    position["x"] = position["x"] + size["width"] / 2;
    position["y"] = position["y"] + size["height"] / 2;

    const qreal speedBullet = bullet->getSpeed();

    const qreal speedX = ((click["x"] - position["x"]) * speedBullet
            / sqrt(qPow(click["x"] - position["x"], 2) + qPow(click["y"] - position["y"], 2)));

    const qreal speedY = ((click["y"] - position["y"]) * speedBullet
            / sqrt(qPow(click["x"] - position["x"], 2) + qPow(click["y"] - position["y"], 2)));

    QMap<QString, qreal> speed;
    speed.insert("speed_x", speedX);
    speed.insert("speed_y", speedY);

    bullet->setSpeedMove(speed);
}

void GameObjects::createScene()
{
    QMap<QString, qreal> position;
    position.insert("x", 0);
    position.insert("y", 0);

    QMap<QString, qreal> size;
    size.insert("width", _sizeScene["width"]);
    size.insert("height", _sizeScene["height"]);

    _scene.insert("scene", new Scene(position, size));

    createWeapons();
}

void GameObjects::createWall()
{
    const QMap<QString, qreal> position = generateXY();

    QMap<QString, qreal> size;
    size.insert("width", 50);
    size.insert("height", 50);

    const int idWall = generateId();

    _walls.insert(idWall, new Wall(position, size, idWall));
}

void GameObjects::createWeapons()
{
    if (!_weapons.isEmpty()) {
        _weapons.clear();
    }

    _weapons.insert("plazma", new Plazma);
    _weapons.insert("blaster", new Blaster);
    _weapons.insert("machine_gun", new MachineGun);
}

QMap <QString, QObject*> GameObjects::getWeapons()
{
    return _weapons;
}

bool GameObjects::isExistPlayer(const QString& nickname)
{
    if (_players.contains(nickname)) {
        qDebug() << "Player" << nickname << "is exist!";

        return true;
    }

    qDebug() << "Player" << nickname << "is not exist!";

    return false;
}

void GameObjects::toPlayers(const QString& nickname, Player* player, const bool operation)
{
    if (operation) {
        qDebug() << "Add player" << nickname << "to player's list...";
        _players.insert(nickname, player);
        return;
    }

    qDebug() << "Remove player" << nickname << "from player's list...";
    _players[nickname]->deleteLater();
    _players.remove(nickname);
}

void GameObjects::toBullets(const int id, Bullet *bullet)
{
    _bullets.insert(id, bullet);

    if (!_bullets.contains(id)) {
        qDebug() << "Bullet" << id << "is not found!";
    }

    setSpeedMove(bullet);
}

void GameObjects::delBullets(const int id)
{
    _bullets[id]->deleteLater();
    _bullets.remove(id);
}

void GameObjects::delWall(const int id)
{
    if (!_walls.contains(id)) {
        qDebug() << "Wall object is not found. Wall id:" << id;

        return;
    }

    _walls[id]->deleteLater();
    _walls.remove(id);
}

int GameObjects::generateId()
{
    return qrand() % (999999 - 100000) + 100000;
}

QMap<QString, qreal> GameObjects::generateXY()
{
    const QMap<QString, qreal> sceneSize = _scene["scene"]->getSize();

    QMap<QString, qreal> posXY;
    posXY.insert("x", qrand() % (static_cast<int>(sceneSize["width"]) - 100) + 1);
    posXY.insert("y", qrand() % (static_cast<int>(sceneSize["height"]) - 100) + 1);

    return posXY;
}

void GameObjects::setLifePlayers(const int lifePlayers)
{
    _lifePlayers = lifePlayers;
}

int GameObjects::getLifePlayers()
{
    return _lifePlayers;
}

void GameObjects::setSpeedPlayers(const qreal speedPlayers)
{
    _speedPlayers = speedPlayers;
}

qreal GameObjects::getSpeedPlayers()
{
    return _speedPlayers;
}

QMap<int, Bullet*> GameObjects::getBullets()
{
    return _bullets;
}

QMap<int, Wall*> GameObjects::getWalls()
{
    return _walls;
}

QMap<QString, Player*> GameObjects::getPlayers()
{
    return _players;
}

QMap<QString, Scene*> GameObjects::getScene()
{
    return _scene;
}

void GameObjects::clearList()
{
    qDeleteAll(_players.begin(), _players.end());
    qDeleteAll(_scene.begin(), _scene.end());
    qDeleteAll(_bullets.begin(), _bullets.end());
    qDeleteAll(_walls.begin(), _walls.end());
    _players.clear();
    _scene.clear();
    _bullets.clear();
    _walls.clear();
}
