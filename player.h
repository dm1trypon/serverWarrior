#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMap>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QMap <QString, qreal> position, qreal speedX, qreal speedY, QString nickname, int id, QObject *parent = nullptr);

    QString getNickname();
    void setSpeed(QMap<QString, qreal> speed);
    void setMove(bool isHold);
    QMap<QString, qreal> getPosition();
    QMap<QString, qreal> getSpeed();
    bool getMove();
    int getIdPlayer();
    void setPosition(QMap<QString, qreal> position);
private:
    qreal _posX;
    qreal _posY;
    qreal _speedX;
    qreal _speedY;
    int _life;
    int _id;
    bool _move = false;
    QString _nickname;
};

#endif // PLAYER_H
