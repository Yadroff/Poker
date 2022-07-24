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
        std::cout << "SERVER STARTED" << std::endl;
    }
    connect(buttonShutDown_, SIGNAL(clicked()), this, SLOT(shutdownServer()));
}

Server::~Server()
{
}

void Server::shutdownServer()
{
    if (!isListen_){
        return;
    }
    foreach(int i, clients_.keys()){
        clients_[i]->close();
        clients_.remove(i);
        std::cout << "REMOVE " << i << " CLIENT" << std::endl;
    }
    tcpServer_->close();
    std::cout << "SERVER CLOSED" << std::endl;
    isListen_ = false;
    this->close();
}

void Server::readData()
{
    foreach (int i, clients_.keys()){
        if (clients_[i]->bytesAvailable()){
            QByteArray readBuff = clients_[i]->readAll();
            std::cout << QString(readBuff).toStdString() << std::endl;
        }
    }
}

void Server::newUser()
{
    if (isListen_){
        while (tcpServer_->hasPendingConnections()){
            std::cout << "NEW CONNECTION" << std::endl;
            auto *clientSocket = tcpServer_->nextPendingConnection();
            int id = clientSocket->socketDescriptor();
            clients_[id] = clientSocket;
            connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readData()));
        }
    }
}



