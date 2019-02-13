#include "workjson.h"

#include <QDebug>
#include <QMap>
#include <QJsonArray>

WorkJson &WorkJson::Instance()
{
    static WorkJson theSingleInstance;
    return theSingleInstance;
}

QJsonObject WorkJson::fromJson(QString data)
{
    return QJsonDocument::fromJson(data.toUtf8()).object();
}

QJsonValue WorkJson::parseJson(QString field, QJsonObject dataJsonObj)
{
    if (dataJsonObj.contains(field))
    {
        qDebug().noquote() << "Json object is not contain field:" << field;
        return {};
    }

    qDebug().noquote() << "Json object is contain field:" << field;

    return dataJsonObj.value(field);
}

QString WorkJson::toJson(QString method)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", method);
    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));
    return data;
}

QString WorkJson::toJsonPlayers(QMap <QString, Player *> players)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "objects");

    QJsonArray playersJsonArr;

    foreach (Player *player, players)
    {
        QJsonObject playerJsonObj;
        playerJsonObj.insert("nickname", player->getNickname());
        playerJsonObj.insert("id_player", player->getIdPlayer());
        QMap <QString, qreal> position = player->getPosition();
        playerJsonObj.insert("pos_x", position["x"]);
        playerJsonObj.insert("pos_y", position["y"]);
        playersJsonArr.append(playerJsonObj);
    }

     dataJsonObj.insert("players", playersJsonArr);

    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));
    return data;
}

QString WorkJson::toJsonError(QString error)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "error");
    dataJsonObj.insert("result", error);
    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));
    return data;
}

QString WorkJson::toJsonConnection(QString nickname, int idPlayer, QMap <QString, qreal> positionPlayer)
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

void WorkJson::toSend(QString data)
{
    emit signalToSend(data);
}
