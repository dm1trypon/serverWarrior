#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QMap>

class Scene : public QObject
{
    Q_OBJECT
public:
    Scene(const QMap<QString, qreal> position, const QMap<QString, qreal> size, QObject *parent = nullptr);

    QMap<QString, qreal> getSize();
    QMap<QString, qreal> getPosition();
private:
    QMap <QString, qreal> _position;
    QMap <QString, qreal> _size;
};

#endif // SCENE_H
