#include "commandconnect.h"
#include <QJsonArray>

CommandConnect::CommandConnect(Table *table, QString &playerName, QTcpSocket *playerSocket)
    :  table_(table), playerName_(playerName), playerSocket_(playerSocket){}

QJsonDocument CommandConnect::exec() {
  QJsonObject obj;
  obj.insert("command", "CONNECT");
  if (!table_->addPlayer(playerName_, playerSocket_, -1)) {
    obj.insert("result", "ALREADY EXISTS");
  } else {
    // TODO: отправить инфу клиенту
    obj.insert("table_name", table_->name());
    QJsonArray players;
    foreach (const Player *player, table_->players().values()) {
      QJsonObject playerJson;
      playerJson.insert("name", player->name());
      playerJson.insert("seat", player->seat());
      playerJson.insert("money", player->coins());
      int combinationSize = player->combination().size();
      playerJson.insert("cards", (combinationSize > 2) ? 2 : combinationSize);
      players.push_back(players);
    }
    obj.insert("players", players);
    obj.insert("pot", table_->pot());
    obj.insert("bet", table_->bet());
  }
  QJsonDocument doc(obj);
  return doc;
}
