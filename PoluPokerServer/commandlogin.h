#ifndef COMMANDLOGIN_H
#define COMMANDLOGIN_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include "command.h"

class CommandLogin : public QObject, public Command
{
    Q_OBJECT
public:
    explicit CommandLogin(QSqlDatabase *base, QString &login, QString &password, QObject *parent = nullptr);
    QByteArray exec();
private:
    QSqlDatabase *base_;
    QString login_;
    QString password_;
signals:

};

#endif // COMMANDLOGIN_H
