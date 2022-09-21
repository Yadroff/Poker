#ifndef COMMANDCONNECT_H
#define COMMANDCONNECT_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>

#include "command.h"
#include "table/player.h"
#include "table/table.h"

class CommandConnect : public Command {
 public:
  explicit CommandConnect(QMap<QString, Table *> &tables_, QString &tableName, QString &playerName, QTcpSocket *playerSocket);
  QJsonDocument exec() override;
  ~CommandConnect() = default;
 private:
  QMap<QString, Table *> &map_;
  QString playerName_;
  QTcpSocket *playerSocket_;
  QString tableName_;
};

#endif // COMMANDCONNECT_H
