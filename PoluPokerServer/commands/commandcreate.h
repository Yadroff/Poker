#ifndef COMMANDCREATE_H
#define COMMANDCREATE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include "command.h"
#include "Table/table.h"

class CommandCreate : public Command
{
public:
    explicit CommandCreate(QMap<QString, Table*> &tables, QString &name, int &size);
    QJsonDocument exec();
    ~CommandCreate() = default;
private:
    QString tableName_;
    int tableSize_;
    QMap<QString, Table*> map_;
signals:

};

#endif // COMMANDCREATE_H
