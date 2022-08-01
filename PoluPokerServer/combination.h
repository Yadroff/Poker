#ifndef COMBINATION_H
#define COMBINATION_H

#include <QObject>
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
    RoyalFlush
};

const quint64 NOMINALS_NUMBER = 13;

class Combination : public QObject
{
    Q_OBJECT
public:
    explicit Combination(QObject *parent = nullptr);
    explicit Combination(const Combination &another);
    explicit Combination(const Card &firstCard, const Card &secondCard, QObject *parent = nullptr);
    void addCard(const Card &card);
    void getCombination();
    void updateCombination();
    friend bool operator<(const Combination &first, const Combination &second);
    friend bool operator==(const Combination &first, const Combination &second);
signals:
private:
    bool checkFlush(const QMap<Suit, quint64> &map);
    QVector<QPair<Nominal, quint64>> checkStraight(const QMap<Nominal, quint64> &nominals);
    bool checkFlushStraight(const quint64 &start, const QVector<Card> &cards_);
    QVector<Card> cards_; // множество карт : <масть, номинал>
    QVector<Card> combinationCards_;
    quint64 combination_;
};

#endif // COMBINATION_H
