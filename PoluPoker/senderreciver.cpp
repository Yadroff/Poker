#include "senderreciver.h"
#include <iostream>

SenderReciver::SenderReciver(QTcpSocket *socket, QObject *parent):
    QObject{parent}, socket_(socket)
{
    connect(socket_, SIGNAL(readyRead()), this, SLOT(readData()));
}

SenderReciver::~SenderReciver()
{
    if (socket_){
        socket_->close();
    }
    delete socket_;
}

void SenderReciver::send(const QString &str)
{
    if (socket_->isOpen()){
        socket_->write(str.toUtf8());
    }
}

void SenderReciver::readData()
{
    QByteArray data = socket_->readAll();
    std::cout << data.toStdString() << std::endl;
    parse(QString(data));
}

void SenderReciver::parse(const QString &data)
{
    QVector<QString> commands = QString(data).split(" ").toVector();
    QString command = commands.first();
    if (command == "LOGIN") { // LOGIN
        parseLogin(commands);
    } else if (command == "REGIST") { // REGIST
        parseRegist(commands);
    }
}

void SenderReciver::parseLogin(const QVector<QString> &commands)
{
    if (commands.size() != 2) {
        QString string;
        for (int i = 1; i < commands.size(); ++i) {
            string.append(commands[i] + " ");
        }
        emit loginRegistFail(string);
    } else {
        if (commands[1] == "SUCCESS") {
            emit loginRegistSuccess();

        } else {
            emit loginRegistFail("Wrong login or password");
        }
    }
}

void SenderReciver::parseRegist(const QVector<QString> &commands)
{
    if (commands.size() != 2) {
        QString string;
        for (int i = 1; i < commands.size(); ++i) {
            string.append(commands[i] + " ");
        }
        if (string.contains("UNIQUE constraint failed")) string = "User already exists";
        emit loginRegistFail(string);
    } else {
        if (commands[1] == "SUCCESS") {
            emit loginRegistSuccess();
        } else {
           emit loginRegistFail("Already exists");
        }
    }
}
