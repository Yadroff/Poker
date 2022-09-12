#ifndef COMMANDCONNECT_H
#define COMMANDCONNECT_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include "command.h"
#include "player.h"
#include "table.h"

class CommandConnect :public Command
{
public:
    explicit CommandConnect(Table *table, QString &playerName, const int &playerID);
    QJsonDocument exec();
    ~CommandConnect() = default;
private:
    Table *table_;
    QString playerName_;
    int playerID_;
};

#endif // COMMANDCONNECT_H
