#ifndef COMMANDCONNECT_H
#define COMMANDCONNECT_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>

#include "command.h"
#include "table/player.h"
#include "table/table.h"

class CommandConnect :public Command
{
public:
    explicit CommandConnect(Table *table, QString &playerName, QTcpSocket *playerSocket);
    QJsonDocument exec() override;
    ~CommandConnect() = default;
private:
    Table *table_;
    QString playerName_;
    QTcpSocket *playerSocket_;
};

#endif // COMMANDCONNECT_H
