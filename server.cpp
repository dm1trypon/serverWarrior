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
        qWarning() << "Failed to start a websocket server!";
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
    qDeleteAll(_clientsList.begin(), _clientsList.end());
}

void Server::onNewConnection()
{
    QWebSocket *pSocket = _webSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);

    pSocket->sendTextMessage(_workJson.toJson("verify"));

    _clientsList << pSocket;
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
            qWarning() << "Nickname already use!";
            pClient->sendTextMessage(_workJson.toJsonError("Nickname already use!"));
            _clientsList.removeAll(pClient);
            pClient->deleteLater();
            return;
        }

        _nameClients.insert(pClient, nickname);
        int idPlayer = _gameObjects.generateId();
        QMap <QString, qreal> positionPlayer = _gameObjects.generateXY();
        _gameObjects.toPlayers(nickname, new Player(_gameObjects.generateXY(), 0, 0, nickname, idPlayer), APPEND);
        sendAll(_workJson.toJsonConnection(nickname, idPlayer, positionPlayer));
        return;
    }

    if (_workJson.fromJson(data).value("method") == "control")
    {
        QString nickname = _workJson.parseJson("nickname", _workJson.fromJson(data)).toString();
        QString key = _workJson.parseJson("key", _workJson.fromJson(data)).toString();
        bool isHold = _workJson.parseJson("hold", _workJson.fromJson(data)).toBool();
        _gameObjects.controlPlayers(nickname, key, isHold);
    }
}

void Server::sendAll(QString data)
{
    foreach (QWebSocket* client, _clientsList)
    {
        qDebug().noquote() << "Send all clients:" << data;
        client->sendTextMessage(data);
    }
}

void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    qDebug() << "Process disconnect client from socket and remove player from players list:" << pClient;

    QString nickname;

    if (!_nameClients.contains(pClient))
    {
        qWarning() << "Warning! Client is not exist in clients list:" << pClient;
        return;
    }

    nickname = _nameClients[pClient];

    qDebug() << "Remove client...:" << pClient;
    _nameClients.remove(pClient);

    qDebug() << "Remove player...:" << nickname;

    if (!_gameObjects.isExistPlayer(nickname))
    {
        qWarning() << "Warning! Player is not exist in players list:" << nickname;
        return;
    }

    QMap <QString, QObject *> players = _gameObjects.getPlayers();

    _gameObjects.toPlayers(nickname, players[nickname], REMOVE);

    if (pClient) {
        _clientsList.removeAll(pClient);
        pClient->deleteLater();
    }

    qDebug() << "Done!";
}
