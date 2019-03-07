#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMap>
#include <QTimer>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(const QMap <QString, qreal> position, const QMap<QString, qreal> size, const QString &nickname, const int id, QObject *parent = nullptr);

    QString getNickname();
    bool getMove();
    bool getShot();
    int getId();
    int getShotSpeed();

    QMap <QString, qreal> getPosition();
    QMap <QString, qreal> getSpeed();
    QMap <QString, qreal> getSize();

    void setPosition(const QMap<QString, qreal> position);
    void setMaxSpeed(const QMap<QString, qreal> speed);
    void setMove(const bool isHold);
    void setShotSpeed(const int shotSpeed);

    QTimer *getShotTimer();

    int getLife();
    void setLife();
    int getScore();
    void setScore();
    void setMaxSpeed(const qreal maxSpeed);
    qreal getMaxSpeed();
private slots:
    void setSpeed();

public slots:
    void setShot();

private:
    const bool REMOVE = false;

    bool _isShot = true;
    qreal _width;
    qreal _height;
    qreal _posX;
    qreal _posY;
    qreal _speedX = 0;
    qreal _speedY = 0;
    qreal _maxSpeedX = 0;
    qreal _maxSpeedY = 0;
    qreal _maxSpeed;
    int _shotSpeed = 10;
    int _life;
    int _score = 0;
    int _id;
    bool _move = false;
    QTimer _speedTimer;
    QTimer *_shotTimer;
    QString _nickname;
    QString _side;
};

#endif // PLAYER_H
