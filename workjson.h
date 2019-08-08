#ifndef WORKJSON_H
#define WORKJSON_H

#include "player.h"
#include "bullet.h"
#include "scene.h"
#include "control.h"

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QWebSocket>

class WorkJson : public QObject
{
    Q_OBJECT

private:
    const bool REMOVE = false;
    const bool APPEND = true;
    int cache_id = 0;

    Control _control;
    QList <QWebSocket *> _clientsList;
    QMap <QWebSocket *, QString> _nameClients;

    WorkJson(const WorkJson& root) = delete;
    WorkJson& operator = (const WorkJson&) = delete;

    void onNextShot(const QString &nickname, const QString &weapon, const QMap<QString, qreal> click,
                    const QMap<QString, qreal> sizeBullet, const QMap<QString, Player *> players);

public:
    WorkJson(){}
    static WorkJson& Instance();

    QJsonValue parseJson(const QString &field, const QJsonObject dataJsonObj);
    QString toJsonVerify();
    QString toJsonError(const QString &error);
    QString toJsonObjects(QMap<QString, Player *> players, const QMap<int, Bullet *> bullets, const QMap<QString, Scene *> scene);
    void toSend(const QString &data);
    void onMethod(const QString &data, QWebSocket *pClient);
    QList <QWebSocket *> getClientsList();

    void setClientsList(QList<QWebSocket *> clientsList);
    void setNameClients(QMap<QWebSocket *, QString> nameClients);
    QMap <QWebSocket *, QString> getNameClients();
signals:
    void signalToSend(QString);
};

#endif // WORKJSON_H
