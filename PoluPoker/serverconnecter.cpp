#include "serverconnecter.h"

const QString SERVER_ANS = "SERVER SEND";

ServerConnecter::ServerConnecter(QObject *parent) :
        QObject(parent) {
    socket_ = new QUdpSocket(this);
    socket_->bind(UDP_SERVER_PORT, QUdpSocket::ShareAddress);
    connect(socket_, SIGNAL(readyRead()), this, SLOT(readData()));
    runFlag = true;
}

void ServerConnecter::readData() {
    QString ans;
    QByteArray datagram;
    QHostAddress address;
    if (socket_->hasPendingDatagrams()) {
        datagram.resize(socket_->pendingDatagramSize());
        socket_->readDatagram(datagram.data(), datagram.size(), &address, &serverPort_);
        if (QString(datagram.data()) == SERVER_ANS) {
            ans = "CONNECTED TO SERVER:" + address.toString().split(":").last();
        } else {
            ans = "CAN'T CONNECT TO SERVER";
        }
    }
    emit finished(ans);
}

void ServerConnecter::run()
{
    if (!socket_->waitForReadyRead(10000)){
        QString ans = "CAN'T CONNECT TO SERVER";
        emit finished(ans);
    }
}

ServerConnecter::~ServerConnecter() {
    delete socket_;
}

void ServerConnecter::setRun(bool run)
{
    runFlag = run;
}
