#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtSql>
#include <QSqlDatabase>

#include "table.h"

const quint16 SERVER_PORT = 7777;
const QString DATA_BASE_PATH = "/home/Yadroff/QT/Poker/PoluPokerServer/users.db";

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();
private:
    QTcpServer *tcpServer_; // сервер
    QMap<int, QTcpSocket*> clients_; // мапа [client, socket]
    bool isListen_ = false; // статус
    QPushButton *buttonShutDown_; // кнопка выключения
    QMap<int, QString> players_; // ники игроков
    QVector<Table *> tables_; // столы
    QSqlDatabase dataBase_;

    QByteArray tables(); // отправить столы
    void addInDataBase(const QString &username, const QString &password);
private slots:
    void newUser(); // новый пользователь
    void shutdownServer(); // выключение сервера
    void readData(); // чтение от пользователей
};
#endif // SERVER_H
