#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "animation.h"
#include "player.h"

#include <QObject>
#include <QMap>

class GameObjects : public QObject
{
    Q_OBJECT

public:
    GameObjects(QObject *parent = nullptr);
    bool isExistPlayer(QString nickname);
    void toPlayers(QString nickname, Player *player, bool operation);

    int generateId();
    QMap<QString, qreal> generateXY();
    QMap<QString, Player *> getPlayers();
    void controlPlayers(QString nickname, QString key, bool isHold);
private:
    const qreal speed = 5;

    QMap <QString, Player *> _players;
    Animation _animation;
};

#endif // GAMEOBJECTS_H
