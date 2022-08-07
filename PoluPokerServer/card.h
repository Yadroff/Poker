#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <iostream>

enum class Suit{
    Diamonds = 0,
    Hearts,
    Clubs,
    Spades,
    Wrong = -1
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
    Ace,
    Wrong = -1
};

const quint32 SUITS_NUMBER = 4;
const quint32 NOMINALS_NUMBER = 13;

class Card : public QObject
{
    Q_OBJECT
public:
    Card(const quint64 &suit, const quint64 &nominal, QObject *parent = nullptr); // конструктор
    Card(const Card &other);

    Card &operator=(const Card &another); // операторы
    bool operator!=(const Card &another);
    friend bool operator<(const Card &lhs, const Card &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Card &card);

    Suit suit() const; // геттеры
    Nominal nominal() const;

    void setSuit(const quint64 &suit);
    void setNominal(const quint64 &nominal);
private:
    Suit suit_;
    Nominal nominal_;

};

#endif // CARD_H
