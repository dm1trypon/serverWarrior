#ifndef WORKJSON_H
#define WORKJSON_H

#include "player.h"

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class WorkJson : public QObject
{
    Q_OBJECT

private:
    WorkJson(const WorkJson& root) = delete;
    WorkJson& operator = (const WorkJson&) = delete;

public:
    WorkJson(){}
    static WorkJson& Instance();

    QJsonObject fromJson(QString data);
    QJsonValue parseJson(QString field, QJsonObject dataJsonObj);
    QString toJson(QString method);
    QString toJsonError(QString error);
    QString toJsonConnection(QString nickname, int idPlayer, QMap<QString, qreal> positionPlayer);
    QString toJsonPlayers(QMap<QString, Player *> players);
    void toSend(QString data);

signals:
    void signalToSend(QString);
};

#endif // WORKJSON_H
