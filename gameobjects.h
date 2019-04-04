﻿#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "player.h"
#include "bullet.h"
#include "plazma.h"
#include "blaster.h"
#include "machinegun.h"
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
    void toPlayers(const QString &nickname, Player *player, const bool operation);

    int generateId();
    QMap <QString, qreal> generateXY();
    QMap <QString, Player *> getPlayers();
    void controlPlayers(const QString &nickname, const QString &key, const bool isHold);
    QMap <QString, Player *> setPlayers(QMap <QString, Player *> players);
    void clearList();
    void createScene();
    QMap <QString, Scene *> getScene();
    qreal getSpeedPlayers();

    void setSizeScene(const QMap <QString, int> sizeScene);

    void toBullets(const int id, Bullet *bullet);
    QMap <int, Bullet *> getBullets();
    void delBullets(const QString &nickname, const int id);
    void setSpeedPlayers(const qreal speedPlayers);

    void setLifePlayers(const int lifePlayers);
    int getLifePlayers();
    QMap<QString, QObject *> getWeapons();
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
