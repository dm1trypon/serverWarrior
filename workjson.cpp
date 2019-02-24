#include "workjson.h"

#include <QDebug>
#include <QMap>
#include <QJsonArray>

WorkJson &WorkJson::Instance()
{
    static WorkJson theSingleInstance;
    return theSingleInstance;
}

QJsonObject WorkJson::fromJson(const QString &data)
{
    return QJsonDocument::fromJson(data.toUtf8()).object();
}

QJsonValue WorkJson::parseJson(const QString &field, const QJsonObject dataJsonObj)
{
    if (dataJsonObj.contains(field))
    {
        qDebug().noquote() << "Json object is not contain field:" << field;
        return {};
    }

    qDebug().noquote() << "Json object is contain field:" << field;

    return dataJsonObj.value(field);
}

QString WorkJson::toJson(const QString &method)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", method);
    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));
    return data;
}

QString WorkJson::toJsonObjects(const QMap <QString, Player *> players, const QMap <int, Bullet *> bullets,  const QMap <QString, Scene *> scene)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "objects");

    QJsonArray playersJsonArr;
    QJsonArray bulletsJsonArr;

    foreach (Player *player, players)
    {
        QJsonObject playerJsonObj;
        playerJsonObj.insert("nickname", player->getNickname());
        playerJsonObj.insert("id_player", player->getId());

        QMap <QString, qreal> position = player->getPosition();
        playerJsonObj.insert("pos_x", position["x"]);
        playerJsonObj.insert("pos_y", position["y"]);

        QMap <QString, qreal> size = player->getSize();
        playerJsonObj.insert("width", size["width"]);
        playerJsonObj.insert("height", size["height"]);

        playersJsonArr.append(playerJsonObj);
    }

    dataJsonObj.insert("players", playersJsonArr);

    foreach (Bullet *bullet, bullets)
    {
        QJsonObject bulletJsonObj;
        bulletJsonObj.insert("nickname", bullet->getNickname());
        bulletJsonObj.insert("id_bullet", bullet->getId());

        QMap <QString, qreal> position = bullet->getPosition();
        bulletJsonObj.insert("pos_x", position["x"]);
        bulletJsonObj.insert("pos_y", position["y"]);

        QMap <QString, qreal> size = bullet->getSize();
        bulletJsonObj.insert("width", size["width"]);
        bulletJsonObj.insert("height", size["height"]);

        bulletsJsonArr.append(bulletJsonObj);
    }

    dataJsonObj.insert("bullets", bulletsJsonArr);

    QJsonObject sceneJsonObj;

    QMap <QString, qreal> size = scene["scene"]->getSize();
    sceneJsonObj.insert("width", size["width"]);
    sceneJsonObj.insert("height", size["height"]);

    QMap <QString, qreal> position = scene["scene"]->getPosition();
    sceneJsonObj.insert("pos_x", position["x"]);
    sceneJsonObj.insert("pos_y", position["y"]);

    dataJsonObj.insert("scene", sceneJsonObj);

    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));
    return data;
}

QString WorkJson::toJsonError(const QString &error)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "error");
    dataJsonObj.insert("result", error);
    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));
    return data;
}

QString WorkJson::toJsonConnection(const QString &nickname, const int idPlayer, const QMap <QString, qreal> positionPlayer)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "connection");
    dataJsonObj.insert("nickname", nickname);
    dataJsonObj.insert("id_player", idPlayer);
    dataJsonObj.insert("pos_x", positionPlayer["x"]);
    dataJsonObj.insert("pos_y", positionPlayer["y"]);
    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));
    return data;
}

QString WorkJson::toJsonDisconnection(const QString &nickname)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "disconnection");
    dataJsonObj.insert("nickname", nickname);
    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));
    return data;
}

QString WorkJson::toJsonRemove(const QString &nickname, const int id)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "remove");
    dataJsonObj.insert("nickname", nickname);
    dataJsonObj.insert("id_bullet", id);
    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));
    qDebug().noquote() << "To remove:" << data;
    return data;
}

void WorkJson::toSend(const QString &data)
{
    emit signalToSend(data);
}
