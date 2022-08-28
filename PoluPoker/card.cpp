#include "card.h"

Card::Card(QObject *parent)
    : QObject(parent), cardDeck_(":/images/cardDeck.png"), rank_(Rank::ace),
    suit_(Suit::hearts) {}

void Card::setCard(const QString &suit, const QString &nominal) {
    if (suit == "Diamonds") {
        suit_ = Suit::diamonds;
    } else if (suit == "Hearts") {
        suit_ = Suit::hearts;
    } else if (suit == "Clubs") {
        suit_ = Suit::clubs;
    } else if (suit == "Spades") {
        suit_ = Suit::spades;
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
    }
}

QPixmap Card::getPixmap() {
    return cardDeck_.copy(xCardSize * (qint64)rank_, yCardSize * (qint64)suit_,
                          xCardSize, yCardSize);
}
