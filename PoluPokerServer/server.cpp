#include "server.h"
#include <iostream>



Server::Server(QWidget *parent)
    : QWidget(parent)
{
    buttonShutDown_ = new QPushButton(this);
    QPixmap pixmap(":/Shutdown_button.jpg");
    QIcon buttonIcon(pixmap);
    buttonShutDown_->setIcon(buttonIcon);
    buttonShutDown_->setIconSize(pixmap.rect().size());
    buttonShutDown_->setFixedSize(pixmap.rect().size());
    tcpServer_ = new QTcpServer;
    connect(tcpServer_, SIGNAL(newConnection()), this, SLOT(newUser()));
    if (!tcpServer_->listen(QHostAddress::LocalHost, SERVER_PORT)){
        perror("Server Listen");
    } else{
        isListen_ = true;
        std::cout << "STATE: SERVER STARTED" << std::endl;
    }
    connect(buttonShutDown_, SIGNAL(clicked()), this, SLOT(shutdownServer()));
    dataBase_ = QSqlDatabase::addDatabase("QSQLITE");
    dataBase_.setHostName("localhost");
    dataBase_.setUserName("root");
    dataBase_.setPassword("");
    dataBase_.setDatabaseName(DATA_BASE_PATH);
    if (dataBase_.open()){
        std::cout << "OPERATION: OPEN DATA BASE: SUCCESS" << std::endl;
        this->addInDataBase("Yadroff", "abc");
    } else{
        std::cout << "OPEARTION: OPEN DATA BASE: FAIL" << std::endl;
    }
}

Server::~Server()
{
}


QByteArray Server::tables()
{
    QByteArray toSend;
    for (auto &table: tables_){
        toSend.append(table->name().toUtf8());
    }
    return toSend;
}

void Server::addInDataBase(const QString &username, const QString &password)
{
    QSqlQuery qry;
    bool ok = qry.prepare("INSERT INTO Users (username, password) "
                          "VALUES (:username, :password)");
    if (!ok) std::cout << qry.lastError().text().toStdString() << std::endl;
    std::cout << (ok == true) << std::endl;
    qry.bindValue(":username", username);
    qry.bindValue(":password", password);

    if (qry.exec()){
        std::cout << "OPERATION: ADD USER: SUCCESS" << std::endl;
    } else{
        std::cout << "OPERATION: ADD USER: FAIL" << std::endl;
        std::cout << qry.lastError().text().toStdString() << std::endl;
    }
}

void Server::shutdownServer()
{
    if (!isListen_){
        return;
    }
    foreach(int i, clients_.keys()){
        clients_[i]->close();
        clients_.remove(i);
        std::cout << "OPEARTION: REMOVE: " << i << " CLIENT" << std::endl;
    }
    tcpServer_->close();
    std::cout << "STATE: SERVER CLOSED" << std::endl;
    isListen_ = false;
    this->close();
}

void Server::readData()
{
    foreach (int i, clients_.keys()){
        if (clients_[i]->bytesAvailable()){
            QByteArray readBuff = clients_[i]->readAll();
            std::cout <<"OPEARTION: RECIVE MESSAGE: " << QString(readBuff).toStdString() << std::endl;
            QVector<QString> commands = QString(readBuff).split(" ").toVector();
            QString command = commands[0];
            QByteArray toSend;
            if (command == "init"){
                std::cout << "STATE: IN INIT" << std::endl;
                toSend.append("TABLES ");
                players_[i] = commands[1];
                toSend.append(this->tables());
                toSend.append("TEST FROM SERVER TO CLIENT");
            }
            if (!toSend.isEmpty()){
                clients_[i]->write(toSend);
                std::cout << "OPERATION: SEND TO CLIENT: " << toSend.toStdString() << std::endl;
            }
        }
    }
}

void Server::newUser()
{
    if (isListen_){
        while (tcpServer_->hasPendingConnections()){
            std::cout << "OPEARTION: NEW CONNECTION" << std::endl;
            auto *clientSocket = tcpServer_->nextPendingConnection();
            int id = clientSocket->socketDescriptor();
            clients_[id] = clientSocket;
            connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readData()));
        }
    }
}



