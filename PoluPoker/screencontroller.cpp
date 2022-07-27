#include "screencontroller.h"
#include <QHostAddress>
#include <QSound>

ScreenController::ScreenController(QObject *parent):
    QObject(parent)
{
    socket_ = new QTcpSocket(this);
    socket_->connectToHost(QHostAddress::LocalHost, SERVER_PORT);
    if (!socket_->waitForConnected()){
        std::cout << "Can not to connect: " << socket_->errorString().toStdString() << std::endl;
        return;
    }
    connect(socket_, SIGNAL(readyRead()), this, SLOT(readingData()));
    this->auth_ = new Authentication();
    this->auth_->show();
    connect(auth_, SIGNAL(needToSend(const QString &)), this, SLOT(sendToServer(const QString &)));
}

ScreenController::~ScreenController()
{

}

void ScreenController::parseLogin(const QVector<QString> &commands)
{
    if (commands.size() != 2){
        QString string;
        for (int i = 1; i < commands.size(); ++i){
            string.append(commands[i] + " ");
        }
        QMessageBox::critical(this->auth_, "LOGIN FATAL", string);
    } else{
        if (commands[1] == "SUCCESS"){
            this->menu_ = new MainWindow;
            this->auth_->close();
            this->menu_->show();
        } else{
            QMessageBox::information(this->auth_, "LOGIN ERROR", "Wrong login or password");
        }
    }
}

void ScreenController::parseRegist(const QVector<QString> &commands)
{
    if (commands.size() != 2){
        QString string;
        for (int i = 1; i < commands.size(); ++i){
            string.append(commands[i] + " ");
        }
        if (string.contains("UNIQUE constraint failed")) string = "User already exists";
        QMessageBox::critical(this->auth_, "LOGIN FATAL", string);
    } else{
        if (commands[1] == "SUCCESS"){
            this->menu_ = new MainWindow;
            this->auth_->close();
            this->menu_->show();
        } else{
            QMessageBox::information(this->auth_, "LOGIN ERROR", "Already exists");
        }
    }
}

void ScreenController::connectToTable(const QString &string)
{
//    QString command = "Connect" + string;
//    socket_->writeDatagram(command.toUtf8(), QHostAddress::LocalHost, SERVER_PORT);
//    menu_->hide();
//    table_ = new Table;
//    table_->show();
}

void ScreenController::createTable(const QString &string)
{

}

void ScreenController::readingData()
{
    QByteArray data = socket_->readAll();
    std::cout << data.toStdString() << std::endl;
    QVector<QString> commands = QString(data).split(" ").toVector();
    QString command = commands.first();
    if (command == "LOGIN"){ // LOGIN
        parseLogin(commands);
    } else if (command == "REGIST"){ // REGIST
        parseRegist(commands);
    }
}

void ScreenController::sendToServer(const QString &command)
{
    socket_->write(command.toUtf8());
    std::cout << "WRITE TO SERVER: " << command.toStdString() << std::endl;
    socket_->waitForReadyRead();
}
