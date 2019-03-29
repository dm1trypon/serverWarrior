#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include <QObject>

class MachineGun : public QObject {
    Q_OBJECT
public:
    MachineGun() {}

public:
    const qreal M_SPEED = 16; // bullet's speed
    const int M_DAMAGE = 3; // bullet's damage
    const int M_TIME_LIFE = 1100; // bullet's time life
    const int RATE_OF_FIRE = 40; // bullet's rate of fire
};


#endif // MACHINEGUN_H
