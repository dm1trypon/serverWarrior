#ifndef PLAZMA_H
#define PLAZMA_H

#include <QObject>

class Plazma : public QObject
{
    Q_OBJECT
public:
    Plazma(){}

public:
    const qreal M_SPEED = 16; // bullet's speed
    const int M_DAMAGE = 17; // bullet's damage
    const int M_TIME_LIFE = 2000; // bullet's time life
    const int RATE_OF_FIRE = 600; // bullet's rate of fire
};

#endif // PLAZMA_H
