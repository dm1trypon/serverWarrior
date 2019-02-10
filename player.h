#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(qreal posX, qreal posY, qreal speedX, qreal speedY, QString nickname, int id, QObject *parent = nullptr);

private:
    qreal _posX;
    qreal _posY;
    qreal _speedX;
    qreal _speedY;
    int _life;
    int _id;
    QString _nickname;
};

#endif // PLAYER_H
