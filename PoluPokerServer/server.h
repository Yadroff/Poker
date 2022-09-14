#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtSql>
#include <QSqlDatabase>
#include <QThread>
#include <QUdpSocket>

#include "Table/table.h"
#include "sender.h"
#include "Commands/command.h"
#include "Commands/commandconnect.h"
#include "Commands/commandcreate.h"
#include "Commands/commandauth.h"

const quint16 SERVER_PORT = 7777;
const QString DATA_BASE_PATH = "./users.db";

class Server : public QWidget {
Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);

    ~Server();
private:
    QTcpServer *tcpServer_; // сервер
    QMap<qint64, QTcpSocket *> clients_; // мапа [clientID, socket]
    bool isListen_ = false; // статус
    QPushButton *buttonShutDown_; // кнопка выключения
    QMap<QTcpSocket *, QString> players_; // ники игроков
    QMap<QString, Table *> tables_; // столы
    QSqlDatabase dataBase_; // БД с пользователями
    QThread *threadBroadcast_;
    Sender *senderBroadcast_;

    QJsonArray tables(); // отправить столы

	void test();
private slots:

    void newUser(); // новый пользователь
    void shutdownServer(); // выключение сервера
    void readData(); // чтение от пользователей
    void disconnectUser();


//signals:
//    void stopBroadcast();
};

#endif // SERVER_H
