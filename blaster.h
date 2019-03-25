#ifndef BLASTER_H
#define BLASTER_H

#include <QObject>

class Blaster : public QObject {
    Q_OBJECT
public:
    Blaster() {}

public:
    const qreal M_SPEED = 18; // bullet's speed
    const int M_DAMAGE = 4; // bullet's damage
    const int M_TIME_LIFE = 900; // bullet's time life
    const int RATE_OF_FIRE = 50; // bullet's rate of fire
};

#endif // BLASTER_H
