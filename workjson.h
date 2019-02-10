#ifndef WORKJSON_H
#define WORKJSON_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class WorkJson : public QObject
{
    Q_OBJECT

public:
    WorkJson(QObject *parent = nullptr);
    QJsonObject fromJson(QString data);
    QJsonValue parseJson(QString field, QJsonObject dataJsonObj);
    QString toJson(QString method);
    QString toJsonError(QString error);
};

#endif // WORKJSON_H
