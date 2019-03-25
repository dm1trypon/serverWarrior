#ifndef CONTROL_H
#define CONTROL_H

#include "player.h"

#include <QMap>

class Control
{
public:
    Control();

    void controlPlayers(const QString &nickname, const QString &key, const bool isHold);

private:
    bool isKeyboardSticking(const QMap<QString, Player *> players,
                            const QString &nickname,
                            const QMap<QString, qreal> speedPlayer,
                            const bool isHold);
};

#endif // CONTROL_H
