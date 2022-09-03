#include "senderreciver.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonParseError>

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
        socket_->write(toJSON(str));
    }
}

QByteArray SenderReciver::toJSON(const QString &string)
{
    auto stringVec = string.split(" ").toVector();
    QJsonObject obj;
    auto command = stringVec[0];
    if (command == "REGIST" or command == "LOGIN"){
        assert(stringVec.size() == 3);
        obj.insert("command", command);
        obj.insert("login", stringVec[1]);
        obj.insert("password", stringVec[2]);
    } else if (command == "CREATE"){
        assert(stringVec.size() == 3);
        obj.insert("command", command);
        obj.insert("name", stringVec[1]);
        obj.insert("size", stringVec[2].toInt());
    } else if (command == "CONNECT"){
        assert(stringVec.size() == 4);
        obj.insert("command", command);
        obj.insert("table_name", stringVec[1]);
        obj.insert("player_name", stringVec[2]);
        obj.insert("coins", stringVec[3].toInt());
    } else if (command == "CHANGE_SEAT"){
        assert(stringVec.size() == 3);
        obj.insert("command", command);
        obj.insert("player_name", stringVec[1]);
        obj.insert("new_seat", stringVec[2]);
    }
    QJsonDocument doc(obj);
    QByteArray arr = doc.toJson(QJsonDocument::Indented);
    std::cout << arr.toStdString() << std::endl;
    return arr;
}

void SenderReciver::readData()
{
    QByteArray data = socket_->readAll();
    QJsonDocument json;
    QJsonParseError jsonError;
    json.fromJson(data, &jsonError);
    if (jsonError.error != QJsonParseError::NoError){
        std::cout << "JSON Error: " << jsonError.errorString().toStdString() << std::endl;
    }
    std::cout << QString(json.toJson(QJsonDocument::Compact)).toStdString() << std::endl;
    parse(json);
}

void SenderReciver::parse(const QJsonDocument &jsonDoc)
{
    QJsonObject obj = jsonDoc.object();
    QString command = obj.value("command").toString();
    if (command == "REGIST" or command == "LOGIN"){
        QString result = obj.value("result").toString();
        if (result == "SUCCESS"){
            emit loginRegistSuccess();
        } else{
            if (result.contains("UNIQUE constraint failed")) result = "User already exists";
            emit loginRegistFail(result);
        }
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
