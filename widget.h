#ifndef WIDGET_H
#define WIDGET_H

#include "server.h"
#include "animation.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
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
    QVBoxLayout *_mainLayout;
    QLabel *_labelPort;
    QLabel *_labelList;
    QLabel *_labelInfo;
    QLineEdit *_inputPort;
    QListWidget *_listClients;
    QPushButton *_buttonStart;
    QPushButton *_buttonStop;
    QPushButton *_buttonMore;
    QTimer _updateTimer;

    void createElements();

    void timer();
    void stopServer();
    void onStopServer();
    void onStartedServer();
    void onErrorServer();

private slots:
    void showClients();
    void startServer();
    void typeList();

};

#endif // WIDGET_H
