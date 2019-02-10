#include "server.h"
#include "player.h"

#include <QWebSocket>
#include <QJsonValue>

Server::Server(quint16 port, QObject *parent) :
    QObject(parent),
    _webSocketServer(new QWebSocketServer(QStringLiteral("WebSocket server for game."),
                                               QWebSocketServer::NonSecureMode, this))
{
    if (!_webSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Failed to start a websocket server!";
        return;
    }

    qDebug() << "Echoserver listening on port" << port;
    connect(_webSocketServer, &QWebSocketServer::newConnection, this, &Server::onNewConnection);
    connect(_webSocketServer, &QWebSocketServer::closed, this, &Server::closed);
}

Server::~Server()
{
    qDebug() << "Stop server...";
    _webSocketServer->close();
    qDeleteAll(clientsList.begin(), clientsList.end());
}

void Server::onNewConnection()
{
    QWebSocket *pSocket = _webSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);

    pSocket->sendTextMessage(_workJson.toJson("verify"));

    clientsList << pSocket;
}

void Server::processTextMessage(QString data)
{
    qDebug() << "Incoming message:" << data;

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    if (_workJson.fromJson(data).value("method") == "verify")
    {
        QString nickname = _workJson.fromJson(data).value("nickname").toString();

        if (_gameObjects.isExistPlayer(nickname))
        {
            pClient->sendTextMessage(_workJson.toJsonError("Nickname already use!"));
            clientsList.removeAll(pClient);
            pClient->deleteLater();
            return;
        }

        _gameObjects.toPlayers(nickname, new Player(100, 100, 0, 0, nickname, _gameObjects.generateId()));
    }
}

void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "socketDisconnected:" << pClient;

    if (pClient) {
        clientsList.removeAll(pClient);
        pClient->deleteLater();
    }
}
