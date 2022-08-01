#include "player.h"

Player::Player(const qint64 &id, const quint64 &seat, QObject *parent)
    : QObject{parent}, id_(id), seat_(seat), combination_(Card(0, 0), Card(0, 1))
{
    coins_ = DEFAULT_COINS;
    combination_.addCard(Card(0, 2));
    combination_.addCard(Card(0, 3));
    combination_.addCard(Card(0, 4));
    combination_.addCard(Card(1, 2));
    combination_.addCard(Card(1, 3));
    combination_.updateCombination();
}

Player::Player(const Player &another):
    id_(another.id_), seat_(another.seat_), combination_(another.combination_)
{
    coins_ = DEFAULT_COINS;
}
