#include "player.h"

Player::Player() {
    name_ = "";
    coins_ = 0;
    seat_ = 0;
}

Player::Player(const QString &name, const qint64 &id, const int &seat,
               QObject *parent)
    : QObject{parent}, id_(id), seat_(seat), combination_() {
    name_ = name;
    coins_ = DEFAULT_COINS;
    //    combination_.updateCombination();
    //    std::cout << combination_;
}

Player::Player(const Player &another)
    : QObject(), name_(another.name()), id_(another.id_), seat_(another.seat_),
    combination_(another.combination_) {
    coins_ = DEFAULT_COINS;
}

QString Player::name() const { return name_; }

Combination Player::combination() const { return combination_; }

void Player::addCard(const Card &card) { combination_.addCard(card); }

Player &Player::operator=(const Player &player) {
    name_ = player.name_;
    id_ = player.id_;
    coins_ = player.coins_;
    seat_ = player.seat_;
    combination_ = player.combination_;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << "NAME: " << player.name_.toStdString() << " COINS: " << player.coins_
       << std::endl;
    os << "COMBINATION:" << std::endl << player.combination_ << std::endl;
    return os;
}

bool operator<(const Player &left, const Player &right) {
    return left.seat_ < right.seat_;
}
