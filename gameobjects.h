#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QObject>
#include <QMap>

class GameObjects : public QObject
{
    Q_OBJECT

public:
    GameObjects(QObject *parent = nullptr);
    bool isExistPlayer(QString nickname);
    void toPlayers(QString nickname, QObject *player, bool operation);

    int generateId();
    QMap<QString, int> generateXY();
    QMap<QString, QObject *> getPlayers();
private:
    QMap <QString, QObject*> _players;
};

#endif // GAMEOBJECTS_H
