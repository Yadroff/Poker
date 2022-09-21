#include "card.h"

Card::Card(QObject *parent)
	: QObject(parent), cardDeck_(":/images/cardDeck.png"), rank_(Rank::closed),
	  suit_(Suit::closed) {}

void Card::setCard(const QString &suit, const QString &nominal) {
  if (suit == "Diamonds") {
	suit_ = Suit::diamonds;
  } else if (suit == "Hearts") {
	suit_ = Suit::hearts;
  } else if (suit == "Clubs") {
	suit_ = Suit::clubs;
  } else if (suit == "Spades") {
	suit_ = Suit::spades;
  } else if (suit == "Closed") {
	suit_ = Suit::closed;
  }
  if (nominal == "Ace") {
	rank_ = Rank::ace;
  } else if (nominal == "Two") {
	rank_ = Rank::two;
  } else if (nominal == "Three") {
	rank_ = Rank::three;
  } else if (nominal == "Four") {
	rank_ = Rank::four;
  } else if (nominal == "Five") {
	rank_ = Rank::five;
  } else if (nominal == "Six") {
	rank_ = Rank::six;
  } else if (nominal == "Seven") {
	rank_ = Rank::seven;
  } else if (nominal == "Eight") {
	rank_ = Rank::eight;
  } else if (nominal == "Nine") {
	rank_ = Rank::nine;
  } else if (nominal == "Ten") {
	rank_ = Rank::ten;
  } else if (nominal == "Jack") {
	rank_ = Rank::jack;
  } else if (nominal == "Queen") {
	rank_ = Rank::queen;
  } else if (nominal == "King") {
	rank_ = Rank::king;
  } else if (nominal == "Closed") {
	rank_ = Rank::closed;
  }
}

QPixmap Card::getPixmap() {
  int x = (rank_ == Rank::closed) ? 0 : (int)rank_;
  int y = (int)suit_;
  return cardDeck_.copy(xCardSize * x, yCardSize * y,
						xCardSize, yCardSize);
}
