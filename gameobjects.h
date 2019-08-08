#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "player.h"
#include "bullet.h"
#include "weapons.h"
#include "scene.h"
#include "workjson.h"

#include <QObject>
#include <QMap>

class GameObjects : public QObject
{
    Q_OBJECT

public:
    GameObjects(QObject *parent = nullptr);
    static GameObjects& Instance();

    bool isExistPlayer(const QString &nickname);

    qreal getSpeedPlayers();

    int generateId();
    int getLifePlayers();

    QMap <QString, qreal> generateXY();
    QMap <QString, Player *> getPlayers();
    QMap <QString, Player *> setPlayers(QMap <QString, Player *> players);
    QMap <QString, Scene *> getScene();
    QMap <int, Bullet *> getBullets();
    QMap<QString, QObject *> getWeapons();

    void toPlayers(const QString &nickname, Player *player, const bool operation);
    void clearList();
    void createScene();
    void setSizeScene(const QMap <QString, int> sizeScene);
    void toBullets(const int id, Bullet *bullet);
    void delBullets(const int id);
    void setSpeedPlayers(const qreal speedPlayers);
    void setLifePlayers(const int lifePlayers);
    void controlPlayers(const QString &nickname, const QString &key, const bool isHold);

private:
    GameObjects(const GameObjects& root) = delete;
    GameObjects& operator = (const GameObjects&) = delete;

    qreal _speedPlayers;
    int _lifePlayers;

    QMap <QString, Player *> _players;
    QMap <int, Bullet*> _bullets;
    QMap <QString, Scene *> _scene;
    QMap <QString, int> _sizeScene;
    QMap <QString, QObject *> _weapons;

    bool isKeyboardSticking(const QString &nickname, const QMap <QString, qreal> speedPlayer, const bool isHold);
    void setSpeedMove(Bullet *bullet);
    void createWeapons();
};

#endif // GAMEOBJECTS_H
