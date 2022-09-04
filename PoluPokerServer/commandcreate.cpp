#include "commandcreate.h"
#include <QDebug>

CommandCreate::CommandCreate(QMap<QString, Table*> &tables, QString &name, int &size, QObject *parent):
    QObject{parent}, tableName_(name), tableSize_(size), map_(tables)
{}

Table *CommandCreate::exec()
{
    if (map_.contains(tableName_)){
        qDebug() << QString("TABLE %1 ALREADY EXISTS").arg(tableName_);
        return nullptr;
    }
    auto table = new Table(tableName_, tableSize_);
    qDebug() << QString("NEW TABLE %1 WITH SIZE %2 CREATED").arg(tableName_).arg(tableSize_);
    return table;
}
