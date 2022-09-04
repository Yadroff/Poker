#ifndef COMMANDCREATE_H
#define COMMANDCREATE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include "command.h"
#include "table.h"

class CommandCreate : public Command, public QObject
{
    Q_OBJECT
public:
    explicit CommandCreate(QMap<QString, Table*> &tables, QString &name, int &size, QObject *parent = nullptr);
    QByteArray exec();
private:
    QString tableName_;
    int tableSize_;
    QMap<QString, Table*> map_;
signals:

};

#endif // COMMANDCREATE_H
