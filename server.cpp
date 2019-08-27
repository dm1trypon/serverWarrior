#include "server.h"
#include "player.h"
#include "gameobjects.h"
#include "workjson.h"

#include <QWebSocket>
#include <QJsonValue>
#include <QJsonObject>

Server::Server(const quint16 port, QObject *parent) :
    QObject(parent),
    _webSocketServer(new QWebSocketServer(QStringLiteral("WebSocket server for game."),
                                               QWebSocketServer::NonSecureMode, this))
{
    if (!_webSocketServer->listen(QHostAddress::Any, port)) {
        qWarning() << "Failed to start a websocket server!";

        return;
    }

    qDebug() << "Echoserver listening on port" << port;

    connect(_webSocketServer, &QWebSocketServer::newConnection, this, &Server::onNewConnection);
    connect(_webSocketServer, &QWebSocketServer::closed, this, &Server::closed);

    _error = false;

    GameObjects::Instance().createScene();

    connect(&WorkJson::Instance(), &WorkJson::signalToSend, this, &Server::sendAll);
}

Server::~Server()
{
    qDebug() << "Stop server...";
    QList <QWebSocket* > clientsList = WorkJson::Instance().getClientsList();
    _webSocketServer->close();
    qDeleteAll(clientsList.begin(), clientsList.end());
    WorkJson::Instance().setClientsList(clientsList);
}

bool Server::getError()
{
    return _error;
}

void Server::onNewConnection()
{
    QWebSocket *pSocket = _webSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);

    pSocket->sendTextMessage(WorkJson::Instance().toJsonVerify());
}

void Server::processTextMessage(const QString &data)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    WorkJson::Instance().onMethod(data, pClient);
}

void Server::sendAll(const QString &data)
{
    foreach(QWebSocket* client, WorkJson::Instance().getClientsList()) {
        client->sendTextMessage(data);
    }
}

void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    qDebug() << "Process disconnect client from socket and remove player from players list:" << pClient;

    QString nickname;

    QMap <QWebSocket *, QString> nameClients = WorkJson::Instance().getNameClients();

    if (!nameClients.contains(pClient)) {
        qWarning() << "Warning! Client is not exist in clients list:" << pClient;
        return;
    }

    nickname = nameClients[pClient];

    qDebug() << "Remove client...:" << pClient;
    nameClients.remove(pClient);

    WorkJson::Instance().setNameClients(nameClients);

    qDebug() << "Remove player...:" << nickname;

    if (!GameObjects::Instance().isExistPlayer(nickname)) {
        qWarning() << "Warning! Player is not exist in players list:" << nickname;

        return;
    }

    QMap <QString, Player *> players = GameObjects::Instance().getPlayers();

    GameObjects::Instance().toPlayers(nickname, players[nickname], REMOVE);

    if (!pClient) {
        return;
    }

    QList <QWebSocket *> clientsList = WorkJson::Instance().getClientsList();
    clientsList.removeAll(pClient);
    pClient->deleteLater();
    WorkJson::Instance().setClientsList(clientsList);

    qDebug() << "Done!";
}
