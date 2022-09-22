#include "player.h"

Player::Player(const QString &name, QObject *parent) :
	QObject{parent}, card_(), cardsCount_(0), name_(name), money_(DEFAULT_COINS), seat_(nullptr) {

}

Player::Player(const QString &name, const int &money, Seat *seat) :
	card_(), cardsCount_(0), name_(name), money_(money), seat_(seat) {
  seat_->addPlayer(name, money_, cardsCount_);
}

void Player::giveCard(const QString &suit, const QString &nominal) {
  card_.setCard(suit, nominal);
  seat_->setCardPixmap(cardsCount_++, card_.getPixmap());
}

void Player::changeSeat(Seat *seat) {
  if (seat_) {
	seat_->free();
  }
  seat_ = seat;
  seat_->addPlayer(name_, money_, cardsCount_);

}

void Player::clearCards() {
  cardsCount_ = 0;
  seat_->hide();
  seat_->show();
}

int Player::money() const {
  return money_;
}

void Player::bet(qint32 &bet) {
  money_ -= bet;
  seat_->changeMoney(money_);
}

void Player::leaveTable() {
  seat_->free();
}
const QString &Player::name() const {
  return name_;
}
void Player::SetName(const QString &name) {
  name_ = name;
}
