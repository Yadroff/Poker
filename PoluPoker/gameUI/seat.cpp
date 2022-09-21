#include "seat.h"

Seat::Seat(QVector<QLabel *> *coins, QVector<QLabel *> *cards, QLabel *place, QLabel *name, QLabel *money,
		   QPushButton *button)
	:
	coins_(coins), cards_(cards), place_(place), name_(name), money_(money), button_(button), isAvailable_(true) {
  hide();
}

void Seat::hide() {
  for (auto *coin : *coins_) {
	coin->hide();
  }
  for (auto *card : *cards_) {
	card->hide();
  }
  name_->hide();
  place_->hide();
  money_->hide();
  button_->show();
}

void Seat::show() {
  for (auto *coin : *coins_) {
	coin->show();
  }
  for (int i = 0; i < cardsCount_; ++i) {
	(*cards_)[i]->show();
  }
  name_->show();
  place_->show();
  money_->show();
  button_->hide();
}

void Seat::addPlayer(const QString &playerName, const int &money, const int &cardsCount) {
  name_->setText(playerName);
  money_->setText(QString::number(money));
  cardsCount_ = cardsCount;
  isAvailable_ = false;
  show();
}

bool Seat::isAvailable() const {
  return isAvailable_;
}

void Seat::free() {
  isAvailable_ = true;
  hide();
}

void Seat::setCardPixmap(const int &number, const QPixmap &pixmap) {
  if (number >= 0 and number < 2) {
	(*cards_)[number]->setPixmap(pixmap);
  }
}

void Seat::changeMoney(const int &newMoney) {
  money_->setText(QString::number(newMoney));
}

void Seat::hideAll() {
  hide();
  button_->hide();
}
