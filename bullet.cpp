#include "bullet.h"
#include "gameobjects.h"

Bullet::Bullet(const QMap <QString, qreal> position,
               const QMap <QString, qreal> size,
               const QMap <QString, qreal> click,
               const QString &nickname,
               const QString &weapon,
               const int id, QObject *parent) :
    QObject (parent),
    _position(position),
    _click(click),
    _size(size),
    _nickname(nickname),
    _weapon(weapon),
    _id(id)
{
    const QMap <QString, QObject*> weapons = GameObjects::Instance().getWeapons();

    _plazma = dynamic_cast<Plazma *>(weapons[weapon]);
    _blaster = dynamic_cast<Blaster *>(weapons[weapon]);

    qDebug() << weapon << _plazma << _blaster << weapons.keys();
    burn();
}

Bullet::~Bullet()
{
    if (_plazma) {
        _plazma = nullptr;

        return;
    }

    _blaster = nullptr;
}

QString Bullet::getWeapon()
{
    return _weapon;
}

void Bullet::burn()
{
    if (_plazma) {
        _tAlive.singleShot(_plazma->M_TIME_LIFE, this, &Bullet::die);

        return;
    }

    _tAlive.singleShot(_blaster->M_TIME_LIFE, this, &Bullet::die);
}

void Bullet::die()
{
    _alive = false;
}

bool Bullet::isAlive()
{
    return _alive;
}

void Bullet::setPosition(const QMap <QString, qreal> position)
{
    _position = position;
}

void Bullet::setSpeedMove(const QMap <QString, qreal> speedMove)
{
    _speedMove = speedMove;
}

QMap <QString, qreal> Bullet::getSpeedMove()
{
    return _speedMove;
}

QString Bullet::getNickname()
{
    return _nickname;
}

qreal Bullet::getSpeed()
{
    if (_plazma) {
        return _plazma->M_SPEED;
    }

    return _blaster->M_SPEED;
}

int Bullet::getTimeLife()
{
    if (_plazma) {
        return _plazma->M_TIME_LIFE;
    }

    return _blaster->M_TIME_LIFE;
}

int Bullet::getDamage()
{
    if (_plazma) {
        return _plazma->M_DAMAGE;
    }

    return _blaster->M_DAMAGE;
}

int Bullet::getId()
{
    return _id;
}

QMap <QString, qreal> Bullet::getPosition()
{
    return _position;
}

QMap <QString, qreal> Bullet::getClick()
{
    return _click;
}

QMap <QString, qreal> Bullet::getSize()
{
    return _size;
}
