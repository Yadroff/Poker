#include "screencontroller.h"
#include <QSound>

ScreenController::ScreenController(QObject *parent) :
    QObject(parent) {
    testTable();
//    thread = new QThread(this);
//    servConnect_ = new ServerConnecter();
//    servConnect_->moveToThread(thread);
//    connect(thread, SIGNAL(started()), servConnect_, SLOT(run()));
//    connect(servConnect_, SIGNAL(finished(const QString &)), this, SLOT(connectToServer(const QString &)));
//    thread->start();
//    this->auth_ = new Authentication();
//    this->auth_->show();
//    connect(auth_, SIGNAL(needToSend(const QString &)), this, SLOT(sendToServer(const QString &)));
}

ScreenController::~ScreenController(){

}


void ScreenController::parseLogin(const QVector<QString> &commands) {
    if (commands.size() != 2) {
        QString string;
        for (int i = 1; i < commands.size(); ++i) {
            string.append(commands[i] + " ");
        }
        QMessageBox::critical(this->auth_, "LOGIN FATAL", string);
    } else {
        if (commands[1] == "SUCCESS") {
            createMenu();

        } else {
            QMessageBox::information(this->auth_, "LOGIN ERROR", "Wrong login or password");
        }
    }
}

void ScreenController::parseRegist(const QVector<QString> &commands) {
    if (commands.size() != 2) {
        QString string;
        for (int i = 1; i < commands.size(); ++i) {
            string.append(commands[i] + " ");
        }
        if (string.contains("UNIQUE constraint failed")) string = "User already exists";
        QMessageBox::critical(this->auth_, "LOGIN FATAL", string);
    } else {
        if (commands[1] == "SUCCESS") {
            createMenu();
        } else {
            QMessageBox::information(this->auth_, "LOGIN ERROR", "Already exists");
        }
    }
}

void ScreenController::createMenu() {
    this->menu_ = new MainWindow;
    this->auth_->close();
    this->menu_->show();
    connect(menu_, SIGNAL(needToSend(const QString &)), this, SLOT(sendToServer(const QString &)));

}

void ScreenController::testTable()
{
//    table_ = new Table();
//    table_->putCardOnTable("Spades", "Ace");
//    table_->putCardOnTable("Diamonds", "Ace");
//    table_->putCardOnTable("Diamonds", "Two");
//    table_->putCardOnTable("Hearts", "Eight");
//    table_->putCardOnTable("Clubs", "Jack");
//    table_->show();
    ui_ = new GameUI("My table", "Yadroff");
    ui_->show();
}

void ScreenController::readingData() {
    QByteArray data = socket_->readAll();
    std::cout << data.toStdString() << std::endl;
    QVector<QString> commands = QString(data).split(" ").toVector();
    QString command = commands.first();
    if (command == "LOGIN") { // LOGIN
        parseLogin(commands);
    } else if (command == "REGIST") { // REGIST
        parseRegist(commands);
    }
}

void ScreenController::sendToServer(const QString &command) {
    socket_->write(command.toUtf8());
    std::cout << "WRITE TO SERVER: " << command.toStdString() << std::endl;
    socket_->waitForReadyRead();
}

void ScreenController::connectToServer(const QString &string) {
    std::cout << string.toStdString() << std::endl;
    thread->quit();
    thread->wait();
    thread->deleteLater();
    servConnect_->deleteLater();
    auto stringList = string.split(":");
    if (stringList.size() < 2) {
        std::cout << "Can not connect to server" << std::endl;
        QMessageBox::critical(this->auth_, "CONNECTION FAIL", string);
        return;
    }
    socket_ = new QTcpSocket(this);
    socket_->connectToHost(stringList.last(), SERVER_PORT);
    if (!socket_->waitForConnected()) {
        std::cout << "Can not to connect: " << socket_->errorString().toStdString() << std::endl;
        QMessageBox::critical(this->auth_, "CONNECTION FAIL", socket_->errorString());
        return;
    }
    std::cout << "CONNECTED TO SERVER: IP: " << stringList.last().toStdString() << std::endl;
    connect(socket_, SIGNAL(readyRead()), this, SLOT(readingData()));
}

