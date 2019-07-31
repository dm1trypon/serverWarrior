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

void GameObjects::delBullets(const QString& nickname, const int id)
{
    delete _bullets[id];
    _bullets.remove(id);

    WorkJson::Instance().toSend(WorkJson::Instance().toJsonRemove(nickname, id));
}

int GameObjects::generateId()
{
    return qrand() % (999999 - 100000) + 100000;;
}

QMap<QString, qreal> GameObjects::generateXY()
{
    QMap<QString, qreal> posXY;
    posXY.insert("x", qrand() % (1000 - 1) + 1);
    posXY.insert("y", qrand() % (1000 - 1) + 1);

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
    _players.clear();
}
