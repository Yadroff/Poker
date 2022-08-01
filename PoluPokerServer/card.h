#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <iostream>

enum class Suit{
    Diamonds = 0,
    Hearts,
    Clubs,
    Spades
};

enum class Nominal{
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

class Card : public QObject
{
    Q_OBJECT
public:
    Card(const quint64 &suit, const quint64 &nominal, QObject *parent = nullptr);
    Card(const Card &other);
    Card &operator=(const Card &another);
    bool operator!=(const Card &another);
    bool operator<(const Card &another);
    friend std::ostream &operator<<(std::ostream &os, const Card &card);
    Suit suit() const;
    Nominal nominal() const;
private:
    Suit suit_;
    Nominal nominal_;

};

#endif // CARD_H
