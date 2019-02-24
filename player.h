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
    void setMaxSpeed(const QMap<QString, qreal> speed);
    void setMove(bool isHold);
    QMap <QString, qreal> getPosition();
    QMap <QString, qreal> getSpeed();
    bool getMove();
    int getId();
    void setPosition(const QMap<QString, qreal> position);
    QMap <QString, qreal> getSize();

    bool getShot();
    QTimer *getShotTimer();
private slots:
    void setSpeed();

public slots:
    void setShot();

private:
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
    int _timeShot = 1;
    int _life;
    int _id;
    bool _move = false;
    QTimer _speedTimer;
    QTimer *_shotTimer;
    QString _nickname;
    QString _side;
};

#endif // PLAYER_H
