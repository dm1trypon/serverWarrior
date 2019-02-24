#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QMap>

class Bullet : public QObject
{
    Q_OBJECT
public:
    Bullet(const QMap <QString, qreal> position, const QMap<QString, qreal> size, const QMap <QString, qreal> click, const QString &nickname, const int id, QObject *parent = nullptr);

    void setPosition(const QMap<QString, qreal> position);
    QString getNickname();
    int getId();
    QMap <QString, qreal> getPosition();
    QMap <QString, qreal> getClick();
    qreal getSpeed();
    QMap <QString, qreal> getSpeedMove();
    void setSpeedMove(const QMap <QString, qreal> speedMove);

    QMap<QString, qreal> getSize();
private:
    const qreal _speed = 7;

    QMap <QString, qreal> _position;
    QMap <QString, qreal> _click;
    QMap <QString, qreal> _size;
    QMap <QString, qreal> _speedMove;

    QString _nickname;
    int _id;
};

#endif // BULLET_H
