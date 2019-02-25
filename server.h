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
    explicit Server(const quint16 port, QObject *parent = nullptr);
    ~Server();

    bool getError();
signals:
    void closed();

private slots:
    void onNewConnection();
    void processTextMessage(const QString &data);
    void socketDisconnected();
    void sendAll(const QString &data);

private:
    const bool REMOVE = false;
    const bool APPEND = true;

    bool _error = true;

    QWebSocketServer *_webSocketServer;
};

#endif // SERVER_H
