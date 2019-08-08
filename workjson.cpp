#include "workjson.h"
#include "gameobjects.h"

#include <QDebug>
#include <QMap>
#include <QJsonArray>
#include <QPointer>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

WorkJson& WorkJson::Instance()
{
    static WorkJson theSingleInstance;
    return theSingleInstance;
}

void WorkJson::onMethod(const QString& data, QWebSocket* pClient)
{
    const QJsonObject dataJsonObj = QJsonDocument::fromJson(data.toUtf8()).object();

    if (dataJsonObj.value("method") == "verify") {
        const QString nickname = dataJsonObj.value("nickname").toString();

        QMap<QString, qreal> posDisplay;
        posDisplay.insert("width", dataJsonObj.value("width").toDouble());
        posDisplay.insert("height", dataJsonObj.value("height").toDouble());

        if (_clientsList.contains(pClient)) {
            return;
        }

        WorkJson::Instance().setClientsList(_clientsList << pClient);

        if (GameObjects::Instance().isExistPlayer(nickname)) {
            qWarning() << "Nickname already use!";
            pClient->sendTextMessage(toJsonError("Nickname already use!"));
            _clientsList.removeAll(pClient);
            pClient->close();
            pClient->deleteLater();

            return;
        }

        _nameClients.insert(pClient, nickname);

        const int idPlayer = GameObjects::Instance().generateId();
        const QMap<QString, qreal> positionPlayer = GameObjects::Instance().generateXY();

        QMap<QString, qreal> sizePlayer;
        sizePlayer.insert("width", 100);
        sizePlayer.insert("height", 100);

        GameObjects::Instance().toPlayers(nickname,
            new Player(positionPlayer, posDisplay, sizePlayer, nickname, idPlayer), APPEND);

        toSend(toJsonObjects(GameObjects::Instance().getPlayers(), GameObjects::Instance().getBullets(),
            GameObjects::Instance().getScene()));

        return;
    }

    if (dataJsonObj.value("method") == "control") {
        const QString nickname = dataJsonObj.value("nickname").toString();
        const QString key = dataJsonObj.value("key").toString();
        const bool isHold = dataJsonObj.value("hold").toBool();

        _control.controlPlayers(nickname, key, isHold);

        return;
    }

    if (dataJsonObj.value("method") == "cursor") {
        const QString nickname = dataJsonObj.value("nickname").toString();

        const qreal clickX = dataJsonObj.value("pos_x").toDouble();
        const qreal clickY = dataJsonObj.value("pos_y").toDouble();

        const bool isShot = dataJsonObj.value("is_shot").toBool();
        const QMap<QString, Player*> players = GameObjects::Instance().getPlayers();

        if (!players.contains(nickname)) {
            return;
        }

        players[nickname]->setIsShooting(isShot);
        players[nickname]->setCursor(QPointF(clickX, clickY));

        if (!isShot) {
            return;
        }

        if (!dataJsonObj.contains("weapon")) {
            qDebug() << "Wrong json, weapon prop of json object is not exist!";

            return;
        }

        const QString weapon = dataJsonObj.value("weapon").toString();

        QMap<QString, qreal> click;
        click.insert("x", clickX);
        click.insert("y", clickY);

        QMap<QString, qreal> sizeBullet;
        sizeBullet.insert("width", 30);
        sizeBullet.insert("height", 30);

        QtConcurrent::run(this, &WorkJson::onNextShot, nickname, weapon, click, sizeBullet, players);

        return;
    }
}

void WorkJson::onNextShot(const QString &nickname, const QString &weapon, const QMap<QString, qreal> click,
                          const QMap<QString, qreal> sizeBullet, const QMap<QString, Player*> players)
{
    while (players[nickname]->getCursor() == QPointF(click["x"], click["y"])) {
        qDebug() << players[nickname]->getCursor() << QPointF(click["x"], click["y"]);
        if (!players[nickname]->getIsShooting()) {
            return;
        }

        const int idBullet = GameObjects::Instance().generateId();

        Player* player = nullptr;

        if (GameObjects::Instance().getPlayers().contains(nickname)) {
            player = GameObjects::Instance().getPlayers()[nickname];
        }

        if (!player) {
            return;
        }

        const QMap<QString, qreal> sizePlayer = player->getSize();
        const QMap<QString, qreal> positionPlayer = player->getPosition();

        QMap<QString, qreal> positionPlayerCenter;
        positionPlayerCenter.insert("x", positionPlayer["x"] + sizePlayer["width"] / 2 - sizeBullet["width"] / 2);
        positionPlayerCenter.insert("y", positionPlayer["y"] + sizePlayer["height"] / 2 - sizeBullet["height"] / 2);

        if (!player->getShot()) {
            continue;
        }

        player->setShot();

        const QMap<QString, QObject*> weapons = GameObjects::Instance().getWeapons();

        if (!weapons.contains(weapon)) {
            return;
        }

        Plazma* plazma = dynamic_cast<Plazma *>(weapons[weapon]);
        Blaster* blaster = dynamic_cast<Blaster *>(weapons[weapon]);
        MachineGun* machineGun = dynamic_cast<MachineGun *>(weapons[weapon]);

        if (plazma) {
            player->getShotTimer()->singleShot(plazma->RATE_OF_FIRE, player, &Player::setShot);
        }

        if (blaster) {
            player->getShotTimer()->singleShot(blaster->RATE_OF_FIRE, player, &Player::setShot);
        }

        if (machineGun) {
            player->getShotTimer()->singleShot(machineGun->RATE_OF_FIRE, player, &Player::setShot);
        }

        GameObjects::Instance().toBullets(idBullet,
            QPointer<Bullet>(new Bullet(positionPlayerCenter, sizeBullet, click, nickname, weapon, idBullet)));
    }
}

void WorkJson::setClientsList(QList<QWebSocket*> clientsList)
{
    _clientsList = clientsList;
}

QList<QWebSocket*> WorkJson::getClientsList()
{
    return _clientsList;
}

void WorkJson::setNameClients(QMap<QWebSocket*, QString> nameClients)
{
    _nameClients = nameClients;
}

QMap<QWebSocket*, QString> WorkJson::getNameClients()
{
    return _nameClients;
}

QJsonValue WorkJson::parseJson(const QString& field, const QJsonObject dataJsonObj)
{
    if (dataJsonObj.contains(field)) {
        qWarning().noquote() << "Json object is not contain field:" << field;
        return {};
    }

    qWarning().noquote() << "Json object is contain field:" << field;

    return dataJsonObj.value(field);
}

QString WorkJson::toJsonVerify()
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "verify");
    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));

    return data;
}

QString WorkJson::toJsonObjects(const QMap<QString, Player*> players,
    const QMap<int, Bullet*> bullets,
    const QMap<QString, Scene*> scene)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "objects");

    QJsonArray playersJsonArr;
    QJsonArray bulletsJsonArr;

    foreach (Player* player, players) {
        QJsonObject playerJsonObj;
        playerJsonObj.insert("nickname", player->getNickname());
        playerJsonObj.insert("id_player", player->getId());

        QMap<QString, qreal> position = player->getPosition();
        playerJsonObj.insert("pos_x", position["x"]);
        playerJsonObj.insert("pos_y", position["y"]);

        QMap<QString, qreal> size = player->getSize();
        playerJsonObj.insert("width", size["width"]);
        playerJsonObj.insert("height", size["height"]);

        playerJsonObj.insert("rotation", player->getRotate());

        playerJsonObj.insert("life", player->getLife());
        playerJsonObj.insert("score", player->getScore());

        playersJsonArr.append(playerJsonObj);
    }

    dataJsonObj.insert("players", playersJsonArr);

    foreach (Bullet* bullet, bullets) {
        if (!bullet) {
            continue;
        }

        const QString nickname = bullet->getNickname();

        QJsonObject bulletJsonObj;
        bulletJsonObj.insert("nickname", nickname);
        bulletJsonObj.insert("weapon", bullet->getWeapon());
        bulletJsonObj.insert("rotation", players[nickname]->getRotate());
        bulletJsonObj.insert("id_bullet", bullet->getId());

        QMap<QString, qreal> position = bullet->getPosition();
        bulletJsonObj.insert("pos_x", position["x"]);
        bulletJsonObj.insert("pos_y", position["y"]);

        QMap<QString, qreal> speed = bullet->getSpeedMove();
        bulletJsonObj.insert("speed_x", speed["speed_x"]);
        bulletJsonObj.insert("speed_y", speed["speed_y"]);

        QMap<QString, qreal> size = bullet->getSize();
        bulletJsonObj.insert("width", size["width"]);
        bulletJsonObj.insert("height", size["height"]);

        bulletsJsonArr.append(bulletJsonObj);
    }

    dataJsonObj.insert("bullets", bulletsJsonArr);

    QJsonObject sceneJsonObj;

    QMap<QString, qreal> size = scene["scene"]->getSize();
    sceneJsonObj.insert("width", size["width"]);
    sceneJsonObj.insert("height", size["height"]);

    QMap<QString, qreal> position = scene["scene"]->getPosition();
    sceneJsonObj.insert("pos_x", position["x"]);
    sceneJsonObj.insert("pos_y", position["y"]);

    dataJsonObj.insert("scene", sceneJsonObj);

    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));

    return data;
}

QString WorkJson::toJsonError(const QString& error)
{
    QJsonObject dataJsonObj;
    dataJsonObj.insert("method", "error");
    dataJsonObj.insert("result", error);
    QJsonDocument dataJsonDoc(dataJsonObj);
    QString data(dataJsonDoc.toJson(QJsonDocument::Compact));

    return data;
}

void WorkJson::toSend(const QString& data)
{
    emit signalToSend(data);
}
