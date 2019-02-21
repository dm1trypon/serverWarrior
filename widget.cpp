#include "widget.h"
#include "gameobjects.h"
#include "player.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    createElements();
    connect(&_updateTimer, &QTimer::timeout, this, &Widget::showClients);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::createElements()
{
    _mainLayout = new QGridLayout;

    _labelPort = new QLabel("Port:");

    _inputPort = new QLineEdit();
    _inputPort->setMaxLength(5);
    _inputPort->setValidator(new QIntValidator(10000, 60000, this));

    _inputWidth = new QLineEdit();
    _inputWidth->setText("1920");
    _inputWidth->setMaxLength(4);
    _inputWidth->setValidator(new QIntValidator(1000, 9999, this));

    _inputHeight = new QLineEdit();
    _inputHeight->setText("1080");
    _inputHeight->setMaxLength(4);
    _inputHeight->setValidator(new QIntValidator(1000, 9999, this));

    _buttonStart = new QPushButton("Start");
    connect(_buttonStart, &QPushButton::clicked, this, &Widget::startServer);

    _buttonStop = new QPushButton("Stop");
    _buttonStop->hide();
    connect(_buttonStop, &QPushButton::clicked, this, &Widget::stopServer);

    _buttonMore = new QPushButton("More");
    connect(_buttonMore, &QPushButton::clicked, this, &Widget::typeList);

    _labelInfo = new QLabel("<H2>Game server</H2>");

    _labelSize = new QLabel("Size scene:");

    _labelList = new QLabel("Connected clients:");

    _listClients = new QListWidget();

    _mainLayout->addWidget(_labelInfo, 1, 1, 1, 3);
    _mainLayout->addWidget(_labelPort, 2, 1, 1, 1);
    _mainLayout->addWidget(_inputPort, 2, 2, 1, 1);
    _mainLayout->addWidget(_buttonStart, 2, 3, 1, 1);
    _mainLayout->addWidget(_buttonStop, 2, 3, 1, 1);
    _mainLayout->addWidget(_labelSize, 3, 1, 1, 1);
    _mainLayout->addWidget(_inputWidth, 3, 2, 1, 1);
    _mainLayout->addWidget(_inputHeight, 3, 3, 1, 1);
    _mainLayout->addWidget(_labelList, 4, 1, 1, 2);
    _mainLayout->addWidget(_buttonMore, 4, 3, 1, 1);
    _mainLayout->addWidget(_listClients, 5, 1, 3, 3);

    setLayout(_mainLayout);
}

void Widget::timers(const bool isStarted)
{
    if (isStarted)
    {
        _updateTimer.start(UPDATE);
        _animation.start();
        return;
    }

    _updateTimer.stop();
    _animation.stop();
}

void Widget::startServer()
{
    _buttonStart->setDisabled(true);
    _port = static_cast<quint16>(_inputPort->text().toInt());
    qDebug() << "Starting server on port:" << _port;
    toSizeScene();
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

void Widget::toSizeScene()
{
    QMap <QString, int> sizeScene;
    sizeScene.insert("width", _inputWidth->text().toInt());
    sizeScene.insert("height", _inputHeight->text().toInt());
    GameObjects::Instance().setSizeScene(sizeScene);
}

void Widget::onStartedServer()
{
    timers(true);
    elements(true);
}

void Widget::onStopServer()
{
    timers(false);
    elements(false);
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

void Widget::elements(const bool isStarted)
{
    if (isStarted)
    {
        _inputPort->hide();
        _labelPort->hide();
        _labelSize->hide();
        _inputWidth->hide();
        _inputHeight->hide();
        _buttonStart->hide();
        _labelInfo->setText("<H2>Server started on port: " + QString::number(_port) + "</H2>");
        _buttonStop->show();
        return;
    }

    _labelInfo->setText("<H2>Game server</H2>");
    _inputPort->show();
    _labelPort->show();
    _buttonStart->show();
    _labelSize->show();
    _inputWidth->show();
    _inputHeight->show();
    _buttonStop->hide();
    _listClients->clear();
    _buttonStart->setDisabled(false);
}
