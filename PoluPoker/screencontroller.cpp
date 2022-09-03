#include "screencontroller.h"
#include <QSound>

const int TABLE_SIZE = 8;

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
    connect(this->auth_, SIGNAL(changeLogin(const QString &)), this, SLOT(setLogin(const QString &)));
}

ScreenController::~ScreenController(){

}

void ScreenController::setLogin(const QString &newLogin)
{
    login_ = newLogin;
}

const QString &ScreenController::login() const
{
    return login_;
}

void ScreenController::loginFail(const QString &error)
{
    QMessageBox::critical(this->auth_, "FAIL", error);
}


void ScreenController::createMenu() {
    this->menu_ = new MainWindow;
    this->auth_->close();
    this->auth_->deleteLater();
    this->menu_->show();
//    connect(menu_, SIGNAL(needToSend(const QString &)), this->senderReciver_, SLOT(send(const QString &)));
    connect(menu_, SIGNAL(signalCreateTable(const QString &)), this, SLOT(createTable(const QString&)));
}

void ScreenController::createTable(const QString &name)
{
    this->table_ = new GameUI(name, login_);
    this->menu_->hide();
    this->menu_->deleteLater();
    QString string = "CREATE " + name + " " + QString::number(TABLE_SIZE);
    senderReciver_->send(string);
}

void ScreenController::connectTable(const QString &name)
{
    this->table_ = new GameUI(name, login_);
    QString command = "CONNECT" + name + " " + login_ + " ";
    senderReciver_->send(command);
    //TODO: достать инфу с сервера
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
    table_ = new GameUI("My table", "Yadroff");
    table_->show();
}


void ScreenController::connectToServer(const QString &string) {
    this->auth_->stopLoad();
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
    auto socket_ = new QTcpSocket();
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

