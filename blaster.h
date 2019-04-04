#ifndef BLASTER_H
#define BLASTER_H

#include <QObject>

class Blaster : public QObject {
    Q_OBJECT
public:
    Blaster() {}

public:
    const qreal M_SPEED = 14; // bullet's speed
    const int M_DAMAGE = 6; // bullet's damage
    const int M_TIME_LIFE = 1500; // bullet's time life
    const int RATE_OF_FIRE = 80; // bullet's rate of fire
    const int M_HEALTH = 10; // bullet's life
};

#endif // BLASTER_H
