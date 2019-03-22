#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QMap>
#include <QTimer>

class Bullet : public QObject
{
    Q_OBJECT
public:
    Bullet(const QMap <QString, qreal> position, const QMap<QString, qreal> size, const QMap <QString, qreal> click, const QString &nickname, const int id, QObject *parent = nullptr);

    void setPosition(const QMap<QString, qreal> position);
    QString getNickname();
    int getId();
    QMap <QString, qreal> getPosition();
    QMap <QString, qreal> getClick();
    qreal getSpeed();
    int getTimeLife();
    void setTimeLife(const int timeLife);
    int getDamage();
    void setDamage(const int damage);
    QMap <QString, qreal> getSpeedMove();
    void setSpeedMove(const QMap <QString, qreal> speedMove);

    QMap<QString, qreal> getSize();
    void setSpeed(const qreal speed);
    bool isAlive();
private slots:
    void die();
private:
    QTimer _tAlive;
    bool _alive = true;
    qreal _speed;
    int _damage = 8;
    int _timeLife = 1000;

    QMap <QString, qreal> _position;
    QMap <QString, qreal> _click;
    QMap <QString, qreal> _size;
    QMap <QString, qreal> _speedMove;

    QString _nickname;
    int _id;
};

#endif // BULLET_H
