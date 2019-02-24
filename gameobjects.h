#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "player.h"
#include "bullet.h"
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
private:
    GameObjects(const GameObjects& root) = delete;
    GameObjects& operator = (const GameObjects&) = delete;

    const qreal speed = 4;

    QMap <QString, Player *> _players;
    QMap <int, Bullet *> _bullets;
    QMap <QString, Scene *> _scene;
    QMap <QString, int> _sizeScene;

    bool isKeyboardSticking(const QString &nickname, const QMap <QString, qreal> speedPlayer, const bool isHold);
    void setBulletSpeed(Bullet *bullet);
};

#endif // GAMEOBJECTS_H
