#include "screencontroller.h"
#include <QSound>

ScreenController::ScreenController(QObject *parent) :
    QObject(parent) {
//    testTable();
    thread = new QThread(this);
    servConnect_ = new ServerConnecter();
    servConnect_->moveToThread(thread);
    connect(thread, SIGNAL(started()), servConnect_, SLOT(run()));
    connect(servConnect_, SIGNAL(finished(const QString &)), this, SLOT(connectToServer(const QString &)));
    thread->start();
    this->auth_ = new Authentication();
    this->auth_->show();
}

ScreenController::~ScreenController(){

}

void ScreenController::loginFail(const QString &error)
{
    QMessageBox::critical(this->auth_, "FAIL", error);
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
    socket_ = new QTcpSocket();
    socket_->connectToHost(stringList.last(), SERVER_PORT);
    if (!socket_->waitForConnected()) {
        std::cout << "Can not to connect: " << socket_->errorString().toStdString() << std::endl;
        QMessageBox::critical(this->auth_, "CONNECTION FAIL", socket_->errorString());
        return;
    }
    std::cout << "CONNECTED TO SERVER: IP: " << stringList.last().toStdString() << std::endl;
    senderReciver_ = new SenderReciver(socket_, this);
    connect(auth_, SIGNAL(needToSend(const QString &)), senderReciver_, SLOT(send(const QString &)));
    connect(senderReciver_, SIGNAL(loginRegistSuccess()), this, SLOT(createMenu()));
    connect(senderReciver_, SIGNAL(loginRegistFail(const QString &)), this, SLOT(loginFail(const QString &)));
}

