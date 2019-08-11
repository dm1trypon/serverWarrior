#ifndef WEAPONS_H
#define WEAPONS_H

#include <QObject>

class Plazma : public QObject
{
    Q_OBJECT
public:
    Plazma(QObject *parent = nullptr) : QObject(parent){}

public:
    const double M_SPEED = 16; // bullet's speed
    const int M_DAMAGE = 17; // bullet's damage
    const int M_TIME_LIFE = 2000; // bullet's time life
    const int RATE_OF_FIRE = 600; // bullet's rate of fire
    const int M_HEALTH = 20; // bullet's life
};

class MachineGun : public QObject
{
    Q_OBJECT
public:
    MachineGun(QObject *parent = nullptr) : QObject(parent){}

public:
    const double M_SPEED = 16; // bullet's speed
    const int M_DAMAGE = 3; // bullet's damage
    const int M_TIME_LIFE = 1100; // bullet's time life
    const int RATE_OF_FIRE = 40; // bullet's rate of fire
    const int M_HEALTH = 2; // bullet's life
};

class Blaster : public QObject
{
    Q_OBJECT
public:
    Blaster(QObject *parent = nullptr) : QObject(parent){}

public:
    const double M_SPEED = 20; // bullet's speed
    const int M_DAMAGE = 6; // bullet's damage
    const int M_TIME_LIFE = 1500; // bullet's time life
    const int RATE_OF_FIRE = 80; // bullet's rate of fire
    const int M_HEALTH = 10; // bullet's life
};

#endif // WEAPONS_H
