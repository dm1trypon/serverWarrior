#include "server.h"
#include "player.h"
#include "gameobjects.h"
#include "workjson.h"

#include <QWebSocket>
#include <QJsonValue>

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
}

Server::~Server()
{
    qDebug() << "Stop server...";
    _webSocketServer->close();
    qDeleteAll(_clientsList.begin(), _clientsList.end());
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
    connect(&WorkJson::Instance(), &WorkJson::signalToSend, this, &Server::sendAll);

    pSocket->sendTextMessage(WorkJson::Instance().toJson("verify"));

    _clientsList << pSocket;
}

void Server::processTextMessage(const QString &data)
{
    qDebug() << "Incoming message:" << data;

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    if (WorkJson::Instance().fromJson(data).value("method") == "verify")
    {
        QString nickname = WorkJson::Instance().fromJson(data).value("nickname").toString();

        if (GameObjects::Instance().isExistPlayer(nickname))
        {
            qWarning() << "Nickname already use!";
            pClient->sendTextMessage(WorkJson::Instance().toJsonError("Nickname already use!"));
            _clientsList.removeAll(pClient);
            pClient->close();
            pClient->deleteLater();
            return;
        }

        _nameClients.insert(pClient, nickname);
        int idPlayer = GameObjects::Instance().generateId();
        QMap <QString, qreal> positionPlayer = GameObjects::Instance().generateXY();

        QMap <QString, qreal> speedPlayer;
        speedPlayer.insert("speed_x", 0);
        speedPlayer.insert("speed_y", 0);

        QMap <QString, qreal> sizePlayer;
        sizePlayer.insert("width", 50);
        sizePlayer.insert("height", 50);

        GameObjects::Instance().toPlayers(nickname, new Player(positionPlayer, speedPlayer, sizePlayer, nickname, idPlayer), APPEND);
        sendAll(WorkJson::Instance().toJsonConnection(nickname, idPlayer, positionPlayer));
        sendAll(WorkJson::Instance().toJsonObjects(GameObjects::Instance().getPlayers(), GameObjects::Instance().getScene()));
        return;
    }

    if (WorkJson::Instance().fromJson(data).value("method") == "control")
    {
        QString nickname = WorkJson::Instance().fromJson(data).value("nickname").toString();
        QString key = WorkJson::Instance().fromJson(data).value("key").toString();
        bool isHold = WorkJson::Instance().fromJson(data).value("hold").toBool();
        qDebug() << "Method:" << WorkJson::Instance().fromJson(data).value("method");
        GameObjects::Instance().controlPlayers(nickname, key, isHold);
    }
}

void Server::sendAll(const QString &data)
{
    foreach (QWebSocket* client, _clientsList)
    {
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

    if (!GameObjects::Instance().isExistPlayer(nickname))
    {
        qWarning() << "Warning! Player is not exist in players list:" << nickname;
        return;
    }

    QMap <QString, Player *> players = GameObjects::Instance().getPlayers();

    GameObjects::Instance().toPlayers(nickname, players[nickname], REMOVE);

    if (pClient) {
        _clientsList.removeAll(pClient);
        pClient->deleteLater();
    }

    sendAll(WorkJson::Instance().toJsonDisconnection(nickname));
    qDebug() << "Done!";
}
