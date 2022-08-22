#include "server.h"
#include <iostream>


Server::Server(QWidget *parent)
        : QWidget(parent) {
    Table table("Abc", 5);
    buttonShutDown_ = new QPushButton(this);
    QPixmap pixmap(":/image/Shutdown_button.jpg");
    QIcon buttonIcon(pixmap);
    buttonShutDown_->setIcon(buttonIcon);
    buttonShutDown_->setIconSize(pixmap.rect().size());
    buttonShutDown_->setFixedSize(pixmap.rect().size());
    tcpServer_ = new QTcpServer(this);
    connect(tcpServer_, SIGNAL(newConnection()), this, SLOT(newUser()));
    if (!tcpServer_->listen(QHostAddress::Any, SERVER_PORT)) {
        perror("Server Listen");
    } else {
        isListen_ = true;
        std::cout << "STATE: SERVER STARTED" << std::endl;
    }
    connect(buttonShutDown_, SIGNAL(clicked()), this, SLOT(shutdownServer()));
    dataBase_ = QSqlDatabase::addDatabase("QSQLITE");
    dataBase_.setDatabaseName(DATA_BASE_PATH);
    if (dataBase_.open()) {
        std::cout << "OPERATION: OPEN DATA BASE: SUCCESS" << std::endl;
    } else {
        std::cout << "OPEARTION: OPEN DATA BASE: FAIL" << std::endl;
    }
}

Server::~Server() {
    if (dataBase_.isOpen()) {
        dataBase_.close();
    }
    shutdownServer();
}


QByteArray Server::tables() {
    QByteArray toSend;
    for (auto &table: tables_) {
        toSend.append(table->name().toUtf8());
    }
    return toSend;
}

QString Server::addInDataBase(const QString &username, const QString &password) {
    QString answer;
    QSqlQuery qry;
    bool ok = qry.prepare("INSERT INTO Users (username, password) "
                          "VALUES (:username, :password)");
    if (!ok) {
        answer = "REGIST " + qry.lastError().text();
        std::cout << "OPERATION: REGIST" << username.toStdString() + " " + password.toStdString() + " "
                  << answer.toStdString() << std::endl;
        return answer;
    }
    qry.bindValue(":username", username);
    qry.bindValue(":password", password);

    if (qry.exec()) {
        answer = "REGIST SUCCESS";
    } else {
        answer = "REGIST " + qry.lastError().text();
    }
    std::cout << "OPEARTION: REGIST " << username.toStdString() + " " + password.toStdString() + " "
              << answer.toStdString() << std::endl;
    return answer;
}

QString Server::checkInDataBase(const QString &username, const QString &password, const qint64 &id) {
    QString answer;
            foreach(auto &j, players_.keys()) {
            if (players_[j] == username) {
                answer = "LOGIN ALREADY LOGGED IN";
                return answer;
            }
        }
    QSqlQuery qry;
    bool ok = qry.prepare("SELECT * FROM Users WHERE username = :username AND password = :password");
    if (!ok) {
        answer = "LOGIN " + qry.lastError().text();
        std::cout << "OPEARTION: LOGIN: " << username.toStdString() << " " << password.toStdString() << " "
                  << answer.toStdString() << std::endl;
        return answer;
    }
    qry.bindValue(":username", username);
    qry.bindValue(":password", password);
    if (!qry.exec()) {
        answer = "LOGIN " + qry.lastError().text();
        std::cout << answer.toStdString() << std::endl;
        return answer;
    }
    if (qry.next()) {
        answer = "LOGIN SUCCESS";
        players_[clients_[id]] = username;
    } else {
        answer = "LOGIN FAIL";
    }
    std::cout << "OPERATION: LOGIN: " << username.toStdString() + " " << password.toStdString() + " "
              << answer.toStdString() << std::endl;
    return answer;
}

QString Server::createTable(const QString &name) {
    QString answer;
    if (tables_.contains(name)) {
        answer = "CREATE_TABLE: EXISTS";
        std::cout << "CREATE TABLE ERROR: ALREADY EXISTS";
    } else {
        tables_.insert(name, new Table(name));
        answer = "CREATE_TABLE: SUCCESS";

    }
    return answer;
}

QString Server::connectToTable(const QString &name, const qint64 &user) {
    if (tables_.contains(name)) {
        if (tables_[name]->addPlayer(players_[clients_[user]], user, 0)) {
            return {"ADD_PLAYER: SUCCESS"};
        } else {
            return {"ADD_PLAYER: ERROR: ALREADY EXISTS"};
        }
    }
    return {"ADD_PLAYER: ERROR: TABLE DOESN'T EXISTS"};
}

void Server::shutdownServer() {
    if (!isListen_) {
        return;
    }
            foreach(qint64 i, clients_.keys()) {
            clients_[i]->close();
            clients_.remove(i);
            std::cout << "OPERATION: REMOVE: " << i << " CLIENT" << std::endl;
        }
    tcpServer_->close();
    std::cout << "STATE: SERVER CLOSED" << std::endl;
    isListen_ = false;
    this->close();
}

void Server::readData() {
            foreach (qint64 i, clients_.keys()) {
            if (clients_[i]->bytesAvailable()) {
                QByteArray readBuff = clients_[i]->readAll();
                std::cout << "OPEARTION: RECIVE MESSAGE: " << QString(readBuff).toStdString() << std::endl;
                QVector<QString> commands = QString(readBuff).split(" ").toVector();
                if (commands.isEmpty()) {
                    continue;
                }
                QString command = commands[0];
                QByteArray toSend;
                if (command == "init") { // INIT MENU
                    std::cout << "STATE: IN INIT" << std::endl;
                    toSend.append("TABLES ");
                    players_[clients_[i]] = commands[1];
                    toSend.append(this->tables());
                    toSend.append("TEST FROM SERVER TO CLIENT");
                } else if (command == "LOGIN") { // LOGIN
                    if (commands.size() != 3) {
                        std::cout << "LOGIN: WRONG FORMAT: SIZE";
                        toSend = "LOGIN WRONG FORMAT";
                    } else {
                        toSend = checkInDataBase(commands[1], commands[2], i).toUtf8();
                    }

                } else if (command == "REGIST") { // REGISTRATION
                    if (commands.size() != 3) {
                        std::cout << "REGIST: WRONG FORMAT: SIZE" << std::endl;
                        toSend = "REGIST WRONG FORMT";
                    } else {
                        toSend = addInDataBase(commands[1], commands[2]).toUtf8();
                    }
                } else if (command == "CREATE") { // CREATE TABLE
                    if (commands.size() != 2) {
                        std::cout << "CREATE: WRONG FORMAT: SIZE";
                        toSend = "CREATE WRONG FORMAT";
                    } else {
                        toSend = createTable(commands[1]).toUtf8();
                        connectToTable(commands[1], i);
                    }
                }
                if (!toSend.isEmpty()) {
                    clients_[i]->write(toSend);
                    std::cout << "OPERATION: SEND TO CLIENT: " << toSend.toStdString() << std::endl;
                }
            }
        }
}

void Server::disconnectUser() {
    auto *client = qobject_cast<QTcpSocket *>(sender());
    qint64 id = -1;
    if (client) {
        for (auto it = clients_.begin(); it != clients_.end(); ++it) {
            if (it.value() == client) {
                id = it.key();
                clients_.erase(it);
                break;
            }
        }
        players_.remove(client);
        std::cout << "OPERATION: DISCONNECT: " << id << std::endl;
        client->deleteLater();
    }
}

void Server::newUser() {
    if (isListen_) {
        while (tcpServer_->hasPendingConnections()) {
            std::cout << "OPERATION: NEW CONNECTION" << std::endl;
            auto *clientSocket = tcpServer_->nextPendingConnection();
            qint64 id = clientSocket->socketDescriptor();
            clients_[id] = clientSocket;
            connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readData()));
            connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnectUser()));
        }
    }
}



