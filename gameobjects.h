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
    void toPlayers(QString nickname, QObject *player);

    int generateId();
private:
    QMap <QString, QObject*> players;
};

#endif // GAMEOBJECTS_H
