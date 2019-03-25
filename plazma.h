#ifndef PLAZMA_H
#define PLAZMA_H

#include <QObject>

class Plazma : public QObject
{
    Q_OBJECT
public:
    Plazma(){}

public:
    const qreal M_SPEED = 10; // bullet's speed
    const int M_DAMAGE = 4; // bullet's damage
    const int M_TIME_LIFE = 700; // bullet's time life
};

#endif // PLAZMA_H
