#ifndef BULLET_H
#define BULLET_H

#include "weapons.h"

#include <QObject>
#include <QMap>
#include <QTimer>

class Bullet : public QObject
{
    Q_OBJECT
public:
    Bullet(const QMap <QString, qreal> position, const QMap<QString, qreal> size, const QMap <QString, qreal> click,
           const QString &nickname, const QString &weapon, const int id, QObject *parent = nullptr);

    ~Bullet();

    void setPosition(const QMap<QString, qreal> position);
    QString getNickname();
    int getId();
    QMap <QString, qreal> getPosition();
    QMap <QString, qreal> getClick();
    qreal getSpeed();
    int getTimeLife();
    int getDamage();
    QMap <QString, qreal> getSpeedMove();
    void setSpeedMove(const QMap <QString, qreal> speedMove);
    QMap<QString, qreal> getSize();
    bool isAlive();
    QString getWeapon();
    void setHealth(const int damage);
    int getHealth();
private slots:
    void die();
private:
    QTimer _tAlive;
    bool _alive = true;

    Plazma *_plazma = nullptr;
    Blaster *_blaster = nullptr;
    MachineGun *_machineGun = nullptr;

    QMap <QString, qreal> _position;
    QMap <QString, qreal> _click;
    QMap <QString, qreal> _size;
    QMap <QString, qreal> _speedMove;

    QString _nickname;
    QString _weapon;

    int _id;
    int _health;
    void burn();
};

#endif // BULLET_H
