#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMap>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QMap <QString, int> position, qreal speedX, qreal speedY, QString nickname, int id, QObject *parent = nullptr);

    QString getNickname();
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
