#include "workjson.h"

#include <QDebug>

WorkJson::WorkJson(QObject *parent) :
    QObject(parent)
{

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

QString WorkJson::toJsonError(QString error)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "error");
    dataJsonObj.insert("result", error);
    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));
    return data;
}
