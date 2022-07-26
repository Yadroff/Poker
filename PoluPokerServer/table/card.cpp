#include "card.h"

Card::Card(const quint64 &suit, const quint64 &nominal, QObject *parent)
	: QObject{parent} {
  switch (suit % SUITS_NUMBER) {
	case 0:suit_ = Suit::Diamonds;
	  break;
	case 1:suit_ = Suit::Hearts;
	  break;
	case 2:suit_ = Suit::Clubs;
	  break;
	case 3:suit_ = Suit::Spades;
	  break;
  }
  switch (nominal % NOMINALS_NUMBER + 2) {
	case 2:nominal_ = Nominal::Two;
	  break;
	case 3:nominal_ = Nominal::Three;
	  break;
	case 4:nominal_ = Nominal::Four;
	  break;
	case 5:nominal_ = Nominal::Five;
	  break;
	case 6:nominal_ = Nominal::Six;
	  break;
	case 7:nominal_ = Nominal::Seven;
	  break;
	case 8:nominal_ = Nominal::Eight;
	  break;
	case 9:nominal_ = Nominal::Nine;
	  break;
	case 10:nominal_ = Nominal::Ten;
	  break;
	case 11:nominal_ = Nominal::Jack;
	  break;
	case 12:nominal_ = Nominal::Queen;
	  break;
	case 13:nominal_ = Nominal::King;
	  break;
	case 14:nominal_ = Nominal::Ace;
	  break;
  }
}

Card::Card(const Card &other) : QObject() {
  suit_ = other.suit_;
  nominal_ = other.nominal_;
}

Card::Card() {
  suit_ = Suit::Wrong;
  nominal_ = Nominal::Wrong;
}

Card &Card::operator=(const Card &another) {
  this->suit_ = another.suit_;
  this->nominal_ = another.nominal_;
  return *this;
}

bool Card::operator!=(const Card &another) {
  return (another.suit_ != suit_ or another.nominal_ != nominal_);
}

bool operator<(const Card &lhs, const Card &rhs) {
  bool ok = (lhs.nominal() == rhs.nominal()) ? lhs.suit() < rhs.suit() : lhs.nominal() < rhs.nominal();
  return ok;
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
  QString nominal, suit;
  switch ((qint32) card.nominal_) {
	case 2:nominal = "Nominal::Two";
	  break;
	case 3:nominal = "Nominal::Three";
	  break;
	case 4:nominal = "Nominal::Four";
	  break;
	case 5:nominal = "Nominal::Five";
	  break;
	case 6:nominal = "Nominal::Six";
	  break;
	case 7:nominal = "Nominal::Seven";
	  break;
	case 8:nominal = "Nominal::Eight";
	  break;
	case 9:nominal = "Nominal::Nine";
	  break;
	case 10:nominal = "Nominal::Ten";
	  break;
	case 11:nominal = "Nominal::Jack";
	  break;
	case 12:nominal = "Nominal::Queen";
	  break;
	case 13:nominal = "Nominal::King";
	  break;
	case 14:nominal = "Nominal::Ace";
	  break;

  }
  switch ((qint32) card.suit_) {
	case 0:suit = "Suit::Diamonds";
	  break;
	case 1:suit = "Suit::Hearts";
	  break;
	case 2:suit = "Suit::Clubs";
	  break;
	case 3:suit = "Suit::Spades";
	  break;
  }

  os << nominal.toStdString() << " " << suit.toStdString();
  return os;
}

Suit Card::suit() const {
  return suit_;
}

Nominal Card::nominal() const {
  return nominal_;
}

void Card::setSuit(const quint64 &suit) {
  if (suit > 3) {
	std::cout << "ERROR: SET SUIT: WRONG SUIT: " << suit << std::endl;
	return;
  }
  switch (suit % SUITS_NUMBER) {
	case 0:suit_ = Suit::Diamonds;
	  break;
	case 1:suit_ = Suit::Hearts;
	  break;
	case 2:suit_ = Suit::Clubs;
	  break;
	case 3:suit_ = Suit::Spades;
	  break;
  }
}

void Card::setNominal(const quint64 &nominal) {
  if (nominal < 2 or nominal > 14) {
	std::cout << "ERROR: SET NOMINAL: WRONG NOMINAL: " << nominal << std::endl;
  }
  switch (nominal % NOMINALS_NUMBER) {
	case 2:nominal_ = Nominal::Two;
	  break;
	case 3:nominal_ = Nominal::Three;
	  break;
	case 4:nominal_ = Nominal::Four;
	  break;
	case 5:nominal_ = Nominal::Five;
	  break;
	case 6:nominal_ = Nominal::Six;
	  break;
	case 7:nominal_ = Nominal::Seven;
	  break;
	case 8:nominal_ = Nominal::Eight;
	  break;
	case 9:nominal_ = Nominal::Nine;
	  break;
	case 10:nominal_ = Nominal::Ten;
	  break;
	case 11:nominal_ = Nominal::Jack;
	  break;
	case 12:nominal_ = Nominal::Queen;
	  break;
	case 13:nominal_ = Nominal::King;
	  break;
	case 14:nominal_ = Nominal::Ace;
	  break;
  }
}
QString Card::suitString() const{
  QString suit;
  switch ((qint32) this->suit_) {
	case 0: suit = "Suit::Diamonds";
	  break;
	case 1: suit = "Suit::Hearts";
	  break;
	case 2: suit = "Suit::Clubs";
	  break;
	case 3: suit = "Suit::Spades";
	  break;
  }
  return suit;
}
QString Card::nominalString() const{
  QString nominal;
  switch ((qint32) nominal_) {
	case 2: nominal = "Nominal::Two";
	  break;
	case 3: nominal = "Nominal::Three";
	  break;
	case 4: nominal = "Nominal::Four";
	  break;
	case 5: nominal = "Nominal::Five";
	  break;
	case 6: nominal = "Nominal::Six";
	  break;
	case 7: nominal = "Nominal::Seven";
	  break;
	case 8: nominal = "Nominal::Eight";
	  break;
	case 9: nominal = "Nominal::Nine";
	  break;
	case 10: nominal = "Nominal::Ten";
	  break;
	case 11: nominal = "Nominal::Jack";
	  break;
	case 12: nominal = "Nominal::Queen";
	  break;
	case 13: nominal = "Nominal::King";
	  break;
	case 14: nominal = "Nominal::Ace";
	  break;
  }
  return nominal;
}
