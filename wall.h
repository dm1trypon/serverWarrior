#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QMap>

class Wall : public QObject
{
    Q_OBJECT
public:
    Wall(const QMap <QString, qreal> position, const QMap <QString, qreal> size, const int id, QObject *parent = nullptr);

    QMap <QString, qreal> getSize();
    QMap <QString, qreal> getPosition();

    int getHealth();
    void setHealth(const int damage);

    int getDamage();
    int getId();
private:
    QMap <QString, qreal> _position;
    QMap <QString, qreal> _size;

    int _health = 20;
    int _id;

    const int DAMAGE = 20;
};

#endif // WALL_H
