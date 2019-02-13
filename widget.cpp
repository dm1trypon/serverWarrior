#include "widget.h"
#include "gameobjects.h"
#include "player.h"
#include "ui_widget.h"

#include <QBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    createElements();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::createElements()
{
    _mainLayout = new QVBoxLayout;

    _labelPort = new QLabel("Port:");

    _inputPort = new QLineEdit();
    _inputPort->setMaxLength(5);
    _inputPort->setValidator(new QIntValidator(10000, 60000, this));

    _buttonStart = new QPushButton("Start");
    connect(_buttonStart, &QPushButton::clicked, this, &Widget::startServer);

    _buttonStop = new QPushButton("Stop");
    _buttonStop->hide();
    connect(_buttonStop, &QPushButton::clicked, this, &Widget::stopServer);

    _buttonMore = new QPushButton("More");
    connect(_buttonMore, &QPushButton::clicked, this, &Widget::typeList);

    _labelInfo = new QLabel("<H2>Game server</H2>");

    _labelList = new QLabel("Connected clients:");

    _listClients = new QListWidget();

    _mainLayout->addWidget(_labelInfo);
    _mainLayout->addWidget(_labelPort);
    _mainLayout->addWidget(_inputPort);
    _mainLayout->addWidget(_buttonStart);
    _mainLayout->addWidget(_buttonStop);
    _mainLayout->addWidget(_labelList);
    _mainLayout->addWidget(_buttonMore);
    _mainLayout->addWidget(_listClients);

    setLayout(_mainLayout);
}

void Widget::timer()
{
    connect(&_updateTimer, &QTimer::timeout, this, &Widget::showClients);
}

void Widget::startServer()
{
    _buttonStart->setDisabled(true);
    _port = static_cast<quint16>(_inputPort->text().toInt());
    qDebug() << "Starting server on port:" << _port;
    _server = new Server(_port);

    if (_server->getError())
    {
        onErrorServer();
        _server->deleteLater();
        return;
    }

    onStartedServer();
}

void Widget::stopServer()
{
    _server->deleteLater();
    GameObjects::Instance().clearList();
    onStopServer();
}

void Widget::typeList()
{
    if (_fullInfo)
    {
        _buttonMore->setText("More");
        _fullInfo = false;
        return;
    }

    _buttonMore->setText("Less");
    _fullInfo = true;
}

void Widget::onStartedServer()
{
    _updateTimer.start(UPDATE);
    _animation.start();
    _inputPort->hide();
    _labelPort->hide();
    _buttonStart->hide();
    _labelInfo->setText("<H2>Server started on port: " + QString::number(_port) + "</H2>");
    _buttonStop->show();
    timer();
}

void Widget::onStopServer()
{
    _updateTimer.stop();
    _animation.stop();
    _labelInfo->setText("<H2>Game server</H2>");
    _inputPort->show();
    _labelPort->show();
    _buttonStart->show();
    _buttonStop->hide();
    _listClients->clear();
    _updateTimer.stop();
    _buttonStart->setDisabled(false);
}

void Widget::onErrorServer()
{
    qWarning() << "Failed start server!";
}

void Widget::showClients()
{
     _listClients->clear();
    foreach (Player *player, GameObjects::Instance().getPlayers())
    {
        if (_fullInfo)
        {
            _listClients->addItem(player->getNickname() + " {PLAYER_ID: "
                                  + QString::number(player->getIdPlayer())
                                  + ", POSITION: [" + QString::number(player->getPosition()["x"])
                                  + ":" + QString::number(player->getPosition()["y"])
                                  + "], MOVE: " + QString::number(player->getMove()) + "}");
        }
        else
        {
            _listClients->addItem(player->getNickname());
        }
    }
}
