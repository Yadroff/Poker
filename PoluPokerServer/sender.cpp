#include "sender.h"
#include <QThread>
#include <iostream>

Sender::Sender() : runningFlag(true), serverPort(45454) {
    socket_ = new QUdpSocket(this);
}

void Sender::run() {
    std::cout << "SENDER: START SENDING" << std::endl;
    while (runningFlag) {
        QByteArray datagram = "SERVER SEND";
        socket_->writeDatagram(datagram, QHostAddress::Broadcast, serverPort);
//        std::cout << "SENDER: SEND: " << ans << std::endl;
        QThread::sleep(2);
    }
    std::cout << "SENDER: END SENDING" << std::endl;
    emit finished();
}

void Sender::setRunningFlag(bool flag)
{
    runningFlag = flag;
}

