#ifndef SERVER_H
#define SERVER_H

#include "gameobjects.h"
#include "workjson.h"

#include <QWebSocketServer>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(quint16 port, QObject *parent = nullptr);
    ~Server();

signals:
    void closed();

private slots:
    void onNewConnection();
    void processTextMessage(QString data);
    void socketDisconnected();

private:
    QWebSocketServer *_webSocketServer;
    QList<QWebSocket *> clientsList;
    GameObjects _gameObjects;
    WorkJson _workJson;
};

#endif // SERVER_H
