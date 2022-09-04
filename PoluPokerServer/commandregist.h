#ifndef COMMANDREGIST_H
#define COMMANDREGIST_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QJsonDocument>
#include "command.h"

class CommandRegist : public QObject, public Command
{
    Q_OBJECT
public:
    explicit CommandRegist(QSqlDatabase *base, QString &login, QString &password, QObject *parent = nullptr);
    QByteArray exec();
private:
    QSqlDatabase *base_;
    QString login_;
    QString password_;
};

#endif // COMMANDREGIST_H
