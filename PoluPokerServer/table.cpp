#include "table.h"

Table::Table(QObject *parent, const QString &name):
    QObject(parent)
{
    name_ = name;
}


QString Table::name() const
{
    return this->name_;
}

QVector<int> Table::players() const
{
    return this->players_;
}
