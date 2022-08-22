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

class Server : public QWidget {
Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);

    ~Server();

private:
    QTcpServer *tcpServer_; // сервер
    QMap<qint64, QTcpSocket *> clients_; // мапа [client, socket]
    bool isListen_ = false; // статус
    QPushButton *buttonShutDown_; // кнопка выключения
    QMap<QTcpSocket *, QString> players_; // ники игроков
    QVector<Table *> tables_; // столы
    QSqlDatabase dataBase_; // БД с пользователями

    QByteArray tables(); // отправить столы
    QString addInDataBase(const QString &username, const QString &password); // добавить пользователя в БД
    QString
    checkInDataBase(const QString &username, const QString &password, const qint64 &id); // проверить пользователя в БД
    QString createTable(const QString &name);

    QString connectToTable(const qint64 &user);

private slots:

    void newUser(); // новый пользователь
    void shutdownServer(); // выключение сервера
    void readData(); // чтение от пользователей
    void disconnectUser();
};

#endif // SERVER_H
