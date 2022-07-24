#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include "table.h"

const quint16 SERVER_PORT = 7777;

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();
private:
    QTcpServer *tcpServer_;
    QMap<int, QTcpSocket*> clients_;
    bool isListen_ = false;
    QPushButton *buttonShutDown_;
private slots:
    void newUser();
    void shutdownServer();
    void readData();
};
#endif // SERVER_H
