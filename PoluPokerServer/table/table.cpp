#include "table.h"
#include <QDateTime>

const int FLOP_CARDS = 4;

/*!
 * Конструктор класса Table
 * @param name - название стола
 * @param size - максимальное количество игроков
 */
Table::Table(const QString &name, const char &size, QObject *parent)
	: QObject(parent),
	  tableCards_(5),
	  usedCards_(52),
	  generator_(QDateTime::currentMSecsSinceEpoch()),
	  curBet_(0),
	  size_(size),
	  winnerComb_(),
	  bank_(0),
	  isActive_(false) {
  name_ = name;
//  test();
}

QString Table::name() const { return this->name_; }

QMap<QString, Player *> Table::players() const { return this->players_; }

/*!
 * Генератор псеводослучайной карты из колоды
 * @return псевдослучайную неиспользованную карту
 */
Card Table::generateCard() {
  int card;
  quint64 nominal, suit;
  do {
	card = generator_.bounded(52);
	nominal = card % 13;
	suit = card / 13;
  } while (usedCards_[card]);
  usedCards_[card] = true;
  //  std::cout << "NOMINAL: " << nominal << std::endl;
  //  std::cout << "SUIT: " << suit << std::endl;
  return {suit, nominal};
}

/*!
 * Большой и малый блайнд
 */
void Table::blind() {
  // small blind
  // big blind
  for (auto *player : gamePlayers_) {
	giveCardToPlayer(player);
  }
}

/*!
 * Flop
 */
void Table::flop() {
  for (int i = 0; i < FLOP_CARDS; ++i) {
	putCardOnTable();
  }
  // торги
}

/*!
 * Tern
 */
void Table::tern() {
  if (winnerComb_.combination() != Combinations::Error) {
	// winner already exists
	return;
  }
  putCardOnTable();
}

/*!
 * Функция выдачи карты игроку
 * @param player - игрок
 */
void Table::giveCardToPlayer(Player *player) {
  Card card = generateCard();
  player->addCard(card);
  QJsonDocument docToPlayer;
  QJsonObject objToPlayer;
  // отправляем JSON игроку
  objToPlayer.insert("command", "ADD_CARD_TO_PLAYER");
  objToPlayer.insert("suit", card.suitString());
  objToPlayer.insert("nominal", card.nominalString());
  docToPlayer.setObject(objToPlayer);
  player->socket()->write(docToPlayer.toJson(QJsonDocument::Indented));
  // отправляем JSON всем остальным
  QJsonDocument docToAll;
  QJsonObject objToAll;
  objToAll.insert("command", "ADD_CARD");
  objToAll.insert("name", player->name());
  docToAll.setObject(objToAll);
  sendToAll(docToAll.toJson(QJsonDocument::Indented));
}

/*!
 * Функция кладет карту на стол (по факту выдает каждому игроку карту)
 */
void Table::putCardOnTable() {
  Card card = generateCard();
  QJsonDocument doc;
  QJsonObject obj;
  obj.insert("command", "PUT_CARD_ON_TABLE");
  obj.insert("suit", card.suitString());
  obj.insert("nominal", card.nominalString());
  doc.setObject(obj);
  for (auto *player : gamePlayers_) {
	player->addCard(card);
  }
  sendToAll(doc.toJson(QJsonDocument::Indented));
}

/*!
 * Функция добавления игрока
 * @param playerName - ник игрока
 * @param socket - сокет для отправки команд сразу "из стола"
 * @param seat - номер места, за которым сидит игрок
 */
bool Table::addPlayer(const QString &playerName, QTcpSocket *socket, const int &seat) {
  if (players_.contains(playerName)) {
	std::cout << "TABLE: " << name_.toStdString() << " : ERROR: ADD PLAYER: ALREADY EXISTS" << std::endl;
	return false;
  }
  auto *player = new Player(playerName, socket, seat);
  players_.insert(playerName, player);
  if (!isActive_) {
	gamePlayers_.insert(playerName, player);
  }
  std::cout << "TABLE: " << name_.toStdString() << ": SUCCESS: ADD PLAYER: " << playerName.toStdString() << std::endl;
  return true;
}

int Table::size() const { return size_; }

/*!
 * Функция вычислений победителей
 * @return вектор указателей на игроков-победителей
 */
QVector<Player *> Table::calculateWinner() {
  QVector<Player *> winners;
  for (auto *player : gamePlayers_) {
	Combination playerComb = player->combination();
	if (winnerComb_ < playerComb) {
	  winnerComb_ = playerComb;
	  winners.clear();
	  winners.push_back(player);
	} else if (winnerComb_ == playerComb) {
	  winners.push_back(player);
	}
  }
  return winners;
}
void Table::betting(const Player &player) {
  auto socket = player.socket();
  QJsonDocument doc;
  QJsonObject obj;
  obj.insert("command", "BET");
  obj.insert("currentBet", QJsonValue(curBet_));
  doc.setObject(obj);
  socket->write(doc.toJson(QJsonDocument::Indented));
  if (!socket->waitForReadyRead()) {
	std::cout << "PLAYER " << player.name().toStdString() << " DIDN'T ANSWERED";
	// обработка этого случая
	playerFold(player);
  }
}
void Table::river() {}
int Table::bet() const { return curBet_; }
int Table::pot() const { return bank_; }
void Table::test() {
  addPlayer("Yadroff", nullptr, 0);
  addPlayer("potnie_yaici", nullptr, 1);
  blind();
  flop();
  tern();

  auto winners = calculateWinner();
  std::cout << "\t WINNER" << std::endl;
  for (auto *player : winners) {
	std::cout << *player << std::endl;
  }
  std::cout << "\tEND WINNER" << std::endl;
  for (auto *player : gamePlayers_) {
	std::cout << *player << std::endl;
  }
}
void Table::playerFold(const Player &player) {
  QString name = player.name();
  gamePlayers_.remove(name);
  QJsonDocument doc = sendChat(name, "FOLD");
  sendToAll(doc.toJson(QJsonDocument::Indented));
}
void Table::sendToAll(const QByteArray &arr) {
  for (const auto &player : players_) {
	player->socket()->write(arr);
  }
}
bool Table::isActive() const {
  return isActive_;
}
void Table::start() {
  QJsonDocument doc = sendChat("SERVER", "START GAME");
  sendToAll(doc.toJson(QJsonDocument::Indented));
  gamePlayers_ = players_;
  curBet_ = 0;
  bank_ = 0;
  isActive_ = true;
  blind();
}
QJsonDocument Table::sendChat(const QString &sender, const QString &message) {
  QJsonDocument doc;
  QJsonObject obj;
  obj.insert("command", "CHAT_MESSAGE");
  obj.insert("sender", sender);
  obj.insert("message", message);
  doc.setObject(obj);
  return doc;
}
void Table::leavePlayer(const QString &playerName) {
  if (players_.contains(playerName)){
	delete players_[playerName];
	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("command", "PLAYER_LEAVE");
	obj.insert("name", playerName);
	doc.setObject(obj);
	sendToAll(doc.toJson(QJsonDocument::Indented));
  }
}
