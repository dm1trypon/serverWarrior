#ifndef BLASTER_H
#define BLASTER_H

#include <QObject>

class Blaster : public QObject {
    Q_OBJECT
public:
    Blaster() {}

public:
    const QString M_PATH = "/"; // path to bullet image
    const qreal M_SPEED = 10; // bullet's speed
    const int M_DAMAGE = 4; // bullet's damage
    const int M_TIME_LIFE = 700; // bullet's time life
};

#endif // BLASTER_H
