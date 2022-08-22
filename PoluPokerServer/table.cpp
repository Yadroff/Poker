#include "table.h"
#include <QDateTime>

const int FLOP_CARDS = 4;

/*!
 * Конструктор класса Table
 * @param name - название стола
 * @param size - максимальное количество игроков
 */
Table::Table(const QString &name, const char &size, QObject *parent)
        : QObject(parent), tableCards_(5), usedCards_(52),
          generator_(QDateTime::currentMSecsSinceEpoch()), curBet_(0), size_(size), winnerComb_(), bank_(0) {
    name_ = name;
    addPlayer("Yadroff", 0, 0);
    addPlayer("potnie_yaici", 1, 1);
    blind();
    flop();
    tern();

    auto winners = calculateWinner();
    std::cout << "\t WINNER" << std::endl;
    for (auto *player: winners) {
        std::cout << *player << std::endl;
    }
    std::cout << "\tEND WINNER" << std::endl;
    for (auto *player: gamePlayers_) {
        std::cout << *player << std::endl;
    }
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
    for (auto *player: gamePlayers_) {
        player->addCard(generateCard());
        player->addCard(generateCard());
    }
}

/*!
 * Флоп
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
 * @param playerName - ник игрока
 */
void Table::giveCardToPlayer(const QString &playerName) {
    for (auto *player: gamePlayers_) {
        if (player->name() == playerName) {
            player->addCard(generateCard());
            return;
        }
    }
}

/*!
 * Функция кладет карту на стол (по факту выдает каждому игроку карту)
 */
void Table::putCardOnTable() {
    Card card = generateCard();
    for (auto *player: gamePlayers_) {
        player->addCard(card);
    }
}

/*!
 * Функция добавления игрока
 * @param playerName - ник игрока
 * @param id - идентификатор для более быстрой отправки команд
 * @param seat - номер места, за которым сидит игрок
 */
bool Table::addPlayer(const QString &playerName, const qint64 &id, const quint64 &seat) {
    if (players_.contains(playerName)) {
        std::cout << "TABLE: " << name_.toStdString() << " : ERROR: ADD PLAYER: ALREADY EXISTS" << std::endl;
        return false;
    }
    auto *player = new Player(playerName, id, seat);
    players_.insert(playerName, player);
    gamePlayers_.insert(playerName, player);
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
    for (auto *player: gamePlayers_) {
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
