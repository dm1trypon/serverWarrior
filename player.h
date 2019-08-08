#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMap>
#include <QTimer>
#include <QPointF>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(const QMap <QString, qreal> position, const QMap <QString, qreal> posDisplay, const QMap<QString, qreal> size, const QString &nickname, const int id, QObject *parent = nullptr);

    QString getNickname();
    bool getMove();
    bool getShot();
    int getId();

    QMap <QString, qreal> getPosition();
    QMap <QString, qreal> getSpeed();
    QMap <QString, qreal> getSize();

    void setPosition(const QMap <QString, qreal> position);
    void setMaxSpeed(const QMap <QString, qreal> speed);
    void setMove(const bool isHold);

    QTimer *getShotTimer();

    int getLife();
    void onDamage(const int damage);
    int getScore();
    void setScore();
    qreal getMaxSpeed();
    void resetLife();
    void setCursor(const QPointF cursor);
    QPointF getCursor();
    void setRotate(const qreal rotate);
    qreal getRotate();
    const QMap <QString, qreal> getPosDisplay();
    void setInertSpeed(const QPointF coef);
    void setIsShooting(const bool isShooting);
    bool getIsShooting();

private slots:
    void inertialBraking();

public slots:
    void setShot();

private:
    const bool REMOVE = false;

    bool _isShot = true;
    qreal _rotate = 0;
    QMap <QString, qreal> _position;
    QMap <QString, qreal> _posDisplay;
    QPointF _cursor;
    qreal _width;
    qreal _height;
    qreal _speedX = 0;
    qreal _speedY = 0;
    qreal _maxSpeedX = 0;
    qreal _maxSpeedY = 0;
    qreal _maxSpeed;
    int _life;
    int _score = 0;
    int _id;
    bool _move = false;
    bool _isShooting  = false;
    QTimer _speedTimer;
    QTimer *_shotTimer;
    QString _nickname;
    QString _side;
};

#endif // PLAYER_H
