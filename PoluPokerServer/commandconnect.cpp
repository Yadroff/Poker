#include "commandconnect.h"

CommandConnect::CommandConnect(Table *table, QString &playerName, const int &playerID, QObject *parent):
    QObject{parent}, table_(table), playerName_(playerName), playerID_(playerID) {}

QByteArray CommandConnect::exec()
{
    QJsonObject obj;
    obj.insert("command", "CONNECT");
    if (!table_->addPlayer(playerName_, playerID_, -1)){
        obj.insert("result", "ALREADY EXISTS");
}
