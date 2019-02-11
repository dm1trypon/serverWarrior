#ifndef SERVER_H
#define SERVER_H

#include "gameobjects.h"
#include "workjson.h"

#include <QWebSocketServer>
#include <QMap>

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
    const bool REMOVE = false;
    const bool APPEND = true;

    QWebSocketServer *_webSocketServer;
    QMap <QWebSocket *, QString> _nameClients;
    QList <QWebSocket *> _clientsList;
    GameObjects _gameObjects;
    WorkJson _workJson;
    void sendAll(QString data);
};

#endif // SERVER_H
