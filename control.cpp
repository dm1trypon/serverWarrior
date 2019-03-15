#include "control.h"
#include "gameobjects.h"

#include <QDebug>

Control::Control()
{

}

void Control::controlPlayers(const QString &nickname, const QString &key, const bool isHold)
{
    const QMap <QString, Player*> players = GameObjects::Instance().getPlayers();
    const qreal speed = GameObjects::Instance().getSpeedPlayers();

    QMap <QString, qreal> speedPlayer;

    if (key == "up")
    {
        speedPlayer.insert("speed_x", 0);
        speedPlayer.insert("speed_y", -speed);
    }

    if (key == "down")
    {
        speedPlayer.insert("speed_x", 0);
        speedPlayer.insert("speed_y", speed);
    }

    if (key == "left")
    {
        speedPlayer.insert("speed_x", -speed);
        speedPlayer.insert("speed_y", 0);
    }

    if (key == "right")
    {
        speedPlayer.insert("speed_x", speed);
        speedPlayer.insert("speed_y", 0);
    }

    if (key == "left_up")
    {
        speedPlayer.insert("speed_x", -speed);
        speedPlayer.insert("speed_y", -speed);
    }

    if (key == "left_down")
    {
        speedPlayer.insert("speed_x", -speed);
        speedPlayer.insert("speed_y", speed);
    }

    if (key == "right_up")
    {
        speedPlayer.insert("speed_x", speed);
        speedPlayer.insert("speed_y", -speed);
    }

    if (key == "right_down")
    {
        speedPlayer.insert("speed_x", speed);
        speedPlayer.insert("speed_y", speed);
    }

    if (isKeyboardSticking(players, nickname, speedPlayer, isHold))
    {
        qWarning() << "Warning! Sticking keybord, check client!";
        return;
    }

    if (!isHold)
    {
        speedPlayer.insert("speed_x", 0);
        speedPlayer.insert("speed_y", 0);
    }

    players[nickname]->setMaxSpeed(speedPlayer);
    players[nickname]->setMove(isHold);
}

bool Control::isKeyboardSticking(const QMap <QString, Player *> players, const QString &nickname, const QMap <QString, qreal> speedPlayer, const bool isHold)
{
    return players[nickname]->getSpeed() == speedPlayer && players[nickname]->getMove() == isHold;
}
