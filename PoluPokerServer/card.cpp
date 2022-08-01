#include "card.h"

const quint64 SUIT_NUMBER = 4;
const quint64 NOMINALS_NUMBER = 13;

Card::Card(const quint64 &suit, const quint64 &nominal, QObject *parent)
    : QObject{parent}
{
    switch (suit % SUIT_NUMBER){
        case 0:
            suit_ = Suit::Diamonds;
            break;
        case 1:
            suit_ = Suit::Hearts;
            break;
        case 2:
            suit_ = Suit::Clubs;
            break;
        case 3:
            suit_ = Suit::Spades;
            break;
    }
    switch (nominal % NOMINALS_NUMBER + 2){
        case 2:
            nominal_ = Nominal::Two;
            break;
        case 3:
            nominal_ = Nominal::Three;
            break;
        case 4:
            nominal_ = Nominal::Four;
            break;
        case 5:
            nominal_ = Nominal::Five;
            break;
        case 6:
            nominal_ = Nominal::Six;
            break;
        case 7:
            nominal_ = Nominal::Seven;
            break;
        case 8:
            nominal_ = Nominal::Eight;
            break;
        case 9:
            nominal_ = Nominal::Nine;
            break;
        case 10:
            nominal_ = Nominal::Ten;
            break;
        case 11:
            nominal_ = Nominal::Jack;
            break;
        case 12:
            nominal_ = Nominal::Queen;
            break;
        case 13:
            nominal_ = Nominal::King;
            break;
        case 14:
            nominal_ = Nominal::Ace;
            break;
    }
}

Card::Card(const Card &other)
{
    suit_ = other.suit_;
    nominal_ = other.nominal_;
}

Card &Card::operator=(const Card &another)
{
    Card ans(another);
    return ans;
}

bool Card::operator!=(const Card &another)
{
    return (another.suit_ != suit_ or another.nominal_ != nominal_);
}

bool Card::operator<(const Card &another)
{
    return (this->nominal_ == another.nominal_) ? this->suit_ < another.suit_ : this->nominal_ < another.nominal_;
}

std::ostream &operator<<(std::ostream &os, const Card &card)
{
    os << "Nominal: " << (quint64) card.nominal_ << " Suit: " << (quint64) card.suit_;
    return os;
}

Suit Card::suit() const
{
    return suit_;
}

Nominal Card::nominal() const
{
    return nominal_;
}
