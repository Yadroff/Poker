#include "table.h"

Table::Table(const QString &name, QObject *parent):
    QObject(parent)
{
    name_ = name;
    Player player(0, 0);
}


QString Table::name() const
{
    return this->name_;
}

QVector<Player> Table::players() const
{
    return this->players_;
}
