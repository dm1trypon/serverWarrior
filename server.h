#ifndef SERVER_H
#define SERVER_H

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

    bool getError();
signals:
    void closed();

private slots:
    void onNewConnection();
    void processTextMessage(QString data);
    void socketDisconnected();
    void sendAll(QString data);

private:
    const bool REMOVE = false;
    const bool APPEND = true;

    bool _error = true;

    QWebSocketServer *_webSocketServer;
    QMap <QWebSocket *, QString> _nameClients;
    QList <QWebSocket *> _clientsList;

};

#endif // SERVER_H
