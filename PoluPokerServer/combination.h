#ifndef COMBINATION_H
#define COMBINATION_H

#include <QObject>
#include <QVector>
#include "card.h"

const quint64 COMBINATION_SIZE = 5;

enum class Combinations {
    HighCard = 0,
    Pair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush,
    Error = -1
};

class Combination : public QObject {
Q_OBJECT
public:
    explicit Combination(QObject *parent = nullptr);

    Combination(const Combination &another);

    explicit Combination(const Card &firstCard, const Card &secondCard, QObject *parent = nullptr);

    void addCard(const Card &card);

    Combinations combination() const;

    void updateCombination();

    friend bool operator<(const Combination &left, const Combination &right);

    friend bool operator>(const Combination &left, const Combination &right);

    friend bool operator==(const Combination &left, const Combination &right);

    Combination &operator=(const Combination &another);

    friend std::ostream &operator<<(std::ostream &os, const Combination &comb);

signals:
private:
    QVector<QPair<Nominal, Suit>> checkStraightFlush(const QVector<Card> &cards, const QVector<Nominal> &straights,
                                                     const QVector<Suit> &flushs); // вектор по причине снизу + лень переделывать
    QVector<Nominal> checkFourOfAKind(
            const QVector<quint64> &nominals); // возвращается вектор по причине: если нет каре - то хз что возвращать
    QVector<QPair<Nominal, Nominal>>
    checkFullHouse(const QVector<Nominal> &sets, const QVector<Nominal> &pairs); // вектор по той же причине
    QVector<Suit> checkFlush(const QVector<quint64> &suits);

    QVector<Nominal> checkStraight(const QVector<quint64> &nominals);

    QVector<Nominal> checkPairs(const QVector<quint64> &nominals);

    QVector<Nominal> checkSets(const QVector<quint64> &nominals);

    void fillStraightFlush(const QVector<QPair<Nominal, Suit>> &straightflush);

    void fillFour(const QVector<Nominal> &kare);

    void fillFullHouse(const QVector<QPair<Nominal, Nominal>> &fullHouse);

    void fillFlush(const QVector<Suit> &flushs);

    void fillStraight(const QVector<Nominal> &straights);

    void fillSet(const QVector<Nominal> &sets);

    void fillTwoPairs(const QVector<Nominal> &pairs);

    void fillPair(const QVector<Nominal> &pairs);

    void fillHighCard();

    QVector<Card> cards_; // множество карт : <масть, номинал>
    QVector<Card> combinationCards_;
    Combinations combination_;
};

#endif // COMBINATION_H
