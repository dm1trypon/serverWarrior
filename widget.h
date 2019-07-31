#ifndef WIDGET_H
#define WIDGET_H

#include "server.h"
#include "animation.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QGridLayout>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    const int UPDATE = 1000;

    bool _fullInfo = false;
    quint16 _port;
    Server *_server;
    Animation _animation;

    Ui::Widget *ui;
    QGridLayout *_mainLayout;
    QLabel *_labelPort;
    QLabel *_labelList;
    QLabel *_labelInfo;
    QLabel *_labelSize;
    QLabel *_labelSpeedPlayers;
    QLabel *_labelLifePlayers;
    QLineEdit *_inputPort;
    QLineEdit *_inputWidth;
    QLineEdit *_inputHeight;
    QLineEdit *_inputSpeedPlayers;
    QLineEdit *_inputLifePlayers;
    QListWidget *_listClients;
    QPushButton *_buttonStart;
    QPushButton *_buttonStop;
    QPushButton *_buttonMore;
    QTimer _updateTimer;

    void createElements();

    void timers(const bool isStarted);
    void stopServer();
    void onStopServer();
    void onStartedServer();
    void onErrorServer();

    void toSizeScene();
    void elements(const bool isStarted);
private slots:
    void showClients();
    void startServer();
    void typeList();

};

#endif // WIDGET_H
