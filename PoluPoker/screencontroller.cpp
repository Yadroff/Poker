#include "screencontroller.h"
#include <QHostAddress>

ScreenController::ScreenController(QObject *parent):
    QObject(parent)
{
    menu_ = new MainWindow();
    socket_ = new QTcpSocket(this);
    socket_->connectToHost(QHostAddress::LocalHost, SERVER_PORT);
    if (!socket_->waitForConnected()){
        std::cout << "Can not to connect: " << socket_->errorString().toStdString() << std::endl;
        return;
    }
    connect(socket_, SIGNAL(readyRead()), this, SLOT(ReadingData()));
    this->auth_ = new Authentication;
    this->auth_->show();
}

ScreenController::~ScreenController()
{
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

void ScreenController::ReadingData()
{
    QByteArray data = socket_->readAll();
    QVector<QString> comands = QString(data).split(" ").toVector();
    QString command = comands.first();
    if (command == "TABLES"){
        for (int i = 1; i < comands.size();++i){
            this->menu_->tables.append(comands[i]);
        }
    }
}
