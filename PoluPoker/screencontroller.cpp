#include "screencontroller.h"
#include <QHostAddress>

ScreenController::ScreenController(QWidget *parent):
    QWidget(parent)
{
    this->setWindowState(Qt::WindowMaximized);
    menu_ = new MainWindow();
    socket_ = new QTcpSocket(this);
    socket_->connectToHost(QHostAddress::LocalHost, SERVER_PORT);
    if (!socket_->waitForConnected()){
        std::cout << "Can not to connect: " << socket_->errorString().toStdString() << std::endl;
        this->close();
    }
    std::cout << "Connect to server" << std::endl;
    QString string = "Hello, World!\n";
    socket_->write(string.toUtf8());
    menu_->show();
    connect(menu_, SIGNAL(createdTable(const QString &)), this, SLOT(createTable(const QString&)));
    connect(socket_, SIGNAL(readyRead()), this, SLOT(ReadingData()));
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

}
