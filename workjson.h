#ifndef WORKJSON_H
#define WORKJSON_H

#include "player.h"
#include "bullet.h"
#include "scene.h"

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

    QJsonObject fromJson(const QString &data);
    QJsonValue parseJson(const QString &field, const QJsonObject dataJsonObj);
    QString toJson(const QString &method);
    QString toJsonError(const QString &error);
    QString toJsonConnection(const QString &nickname, const int idPlayer, const QMap<QString, qreal> positionPlayer);
    QString toJsonObjects(QMap<QString, Player *> players, const QMap<int, Bullet *> bullets, const QMap<QString, Scene *> scene);
    void toSend(const QString &data);
    QString toJsonDisconnection(const QString &nickname);

    QString toJsonRemove(const QString &nickname, const int id);
signals:
    void signalToSend(QString);
};

#endif // WORKJSON_H
