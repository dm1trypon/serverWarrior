#ifndef ANIMATION_H
#define ANIMATION_H

#include "player.h"

#include <QObject>
#include <QTimer>
#include <QMap>

class Animation : public QObject
{
    Q_OBJECT

public:
    Animation(QObject *parent = nullptr);

    void setObjects(QMap<QString, Player *> objects);
private slots:
    void process();
private:
    const int FPS = 30;

    QMap <QString, Player *> _objects;
    QTimer _animationTimer;
    void start();
    void stop();
};

#endif // ANIMATION_H
