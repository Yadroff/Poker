#include "player.h"

Player::Player(const qint64 &id, const quint64 &seat, QObject *parent)
    : QObject{parent}, id_(id), seat_(seat), combination_(Card(0, 12), Card(0, 11))
{
    coins_ = DEFAULT_COINS;
    combination_.addCard(Card(0, 10));
    combination_.addCard(Card(0, 9));
    combination_.addCard(Card(0, 8));
    combination_.addCard(Card(0, 6));
    combination_.addCard(Card(0, 7));
    combination_.updateCombination();
    std::cout << combination_;
}

Player::Player(const Player &another):
    id_(another.id_), seat_(another.seat_), combination_(another.combination_)
{
    coins_ = DEFAULT_COINS;
}
