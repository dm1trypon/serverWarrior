#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMap>
#include <QTimer>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QMap <QString, qreal> position, QMap<QString, qreal> speed, QMap<QString, qreal> size, const QString &nickname, const int id, QObject *parent = nullptr);

    QString getNickname();
    void setSpeed(const QMap<QString, qreal> speed);
    void setMove(bool isHold);
    QMap <QString, qreal> getPosition();
    QMap <QString, qreal> getSpeed();
    bool getMove();
    int getIdPlayer();
    void setPosition(const QMap<QString, qreal> position);
    QMap <QString, qreal> getSize();
    QMap<QString, qreal> getOldPosition();
private slots:
    void setSlowSpeed();
private:
    qreal _width;
    qreal _height;
    qreal _posX;
    qreal _posY;
    qreal _posXold;
    qreal _posYold;
    qreal _speedX;
    qreal _speedY;
    qreal _speedCoefX = 0;
    qreal _speedCoefY = 0;
    int _life;
    int _id;
    bool _move = false;
    QTimer _speedTimer;
    QString _nickname;
    QString _side;
    void setOldPosition(const QMap<QString, qreal> oldPosition);
};

#endif // PLAYER_H
