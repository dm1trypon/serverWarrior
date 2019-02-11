#include "player.h"

Player::Player(QMap <QString, qreal> position, qreal speedX, qreal speedY, QString nickname, int id, QObject *parent) :
    QObject(parent),
    _posX(position["X"]), _posY(position["Y"]),
    _speedX(speedX), _speedY(speedY),
    _id(id),
    _nickname(nickname)
{

}

QString Player::getNickname()
{
    return _nickname;
}
