#ifndef COMMANDCONNECT_H
#define COMMANDCONNECT_H

#include <QObject>
#include "player.h"
#include "table.h"

class CommandConnect : public QObject
{
    Q_OBJECT
public:
    explicit CommandConnect(Table *table, QString &playerName, QObject *parent = nullptr);
    QByteArray
private:
    Table *table_;
    QString playerName_;
signals:

};

#endif // COMMANDCONNECT_H
