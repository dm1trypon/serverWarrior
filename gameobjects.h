#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "player.h"

#include <QObject>
#include <QMap>

class GameObjects : public QObject
{
    Q_OBJECT

public:
    GameObjects(QObject *parent = nullptr);
    static GameObjects& Instance();

    bool isExistPlayer(QString nickname);
    void toPlayers(QString nickname, Player *player, bool operation);

    int generateId();
    QMap<QString, qreal> generateXY();
    QMap<QString, Player *> getPlayers();
    void controlPlayers(QString nickname, QString key, bool isHold);
    QMap<QString, Player *> setPlayers(QMap<QString, Player *> players);
    void clearList();
private:
    GameObjects(const GameObjects& root) = delete;
    GameObjects& operator = (const GameObjects&) = delete;

    const qreal speed = 10;

    QMap <QString, Player *> _players;
    bool isKeyboardSticking(QString nickname, QMap<QString, qreal> speedPlayer, bool isHold);
};

#endif // GAMEOBJECTS_H
