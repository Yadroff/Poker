#ifndef COMMANDCONNECT_H
#define COMMANDCONNECT_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include "command.h"
#include "table/player.h"
#include "table/table.h"

class CommandConnect :public Command
{
public:
    explicit CommandConnect(Table *table, QString &playerName, const int &playerID);
    QJsonDocument exec() override;
    ~CommandConnect() = default;
private:
    Table *table_;
    QString playerName_;
    int playerID_;
};

#endif // COMMANDCONNECT_H
