#include "commandconnect.h"
#include <QJsonArray>

CommandConnect::CommandConnect(QMap<QString, Table *> &table,
							   QString &tableName,
							   QString &playerName,
							   QTcpSocket *playerSocket)
	: map_(table), playerName_(playerName), playerSocket_(playerSocket), tableName_(tableName) {}

QJsonDocument CommandConnect::exec() {
  QJsonObject obj;
  obj.insert("command", "CONNECT");
  if (!map_.contains(tableName_)){
	obj.insert("result", "TABLE DOESN'T EXISTS");
	return QJsonDocument(obj);
  }
  auto table = map_[tableName_];
  if (!table->addPlayer(playerName_, playerSocket_, -1)){
	obj.insert("result", "ALREADY EXISTS");
	return QJsonDocument(obj);
  }
  obj.insert("result", "SUCCESS");
  obj.insert("pot", table->pot());
  obj.insert("bet", table->bet());
  QJsonArray arr;
  auto players = table->players().values();
  for (const auto player: players){
	QJsonObject playerObj;
	playerObj.insert("name", player->name());
	playerObj.insert("seat", player->seat());
	playerObj.insert("money", player->coins());
	auto combSize = player->combination().size();
	playerObj.insert("cards", (combSize <= 2) ? combSize : 2);
	arr.append(playerObj);
  }
  return QJsonDocument(obj);
}
