#include "screencontroller.h"
#include <QSound>

ScreenController::ScreenController(QObject *parent):
    QObject(parent)
{
    hasServerAddress_ = false;
    udpSocket_ = new QUdpSocket(this);
    udpSocket_->bind(45454, QUdpSocket::ShareAddress);
    connect(udpSocket_, &QUdpSocket::readyRead, this, &ScreenController::connectToServer);
    if (!udpSocket_->waitForReadyRead()){
        std::cout << "Can not connect to server" << std::endl;
    }
    delete udpSocket_;
//    std::cout << "HERE" << std::endl;
    socket_ = new QTcpSocket(this);
    socket_->connectToHost(serverAddress_, 7777);
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

void ScreenController::getHost(QString &ip, quint16 &port)
{
    QFile file("host.config");
    if (!file.open(QIODevice::ReadOnly)){
        perror("Can not open config file");
    }
    QTextStream input(&file);
    QString info = input.readLine();

    //invalid format.
    if(info.split(':').size() != 2) return;

    ip = info.split(':')[0];
    port = QString(info.split(':')[1]).toUInt();
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
            createMenu();

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
            createMenu();
        } else{
            QMessageBox::information(this->auth_, "LOGIN ERROR", "Already exists");
        }
    }
}

void ScreenController::createMenu()
{
    this->menu_ = new MainWindow;
    this->auth_->close();
    this->menu_->show();
    connect(menu_, SIGNAL(needToSend(const QString &)), this, SLOT(sendToServer(const QString &)));

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

void ScreenController::connectToServer()
{
    QByteArray datagram;
    while (udpSocket_->hasPendingDatagrams()){
        QHostAddress address;
        datagram.resize(udpSocket_->pendingDatagramSize());
        udpSocket_->readDatagram(datagram.data(), datagram.size(), &address, &serverPort_);
        std::cout << QString(datagram.data()).toStdString() << std::endl;
        serverAddress_ = address.toString().split(":").last();
        std::cout << serverAddress_.toStdString() << std::endl;
        hasServerAddress_ = true;
    }
}
