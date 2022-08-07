#include "combination.h"

#include <QMap>
#include <algorithm>
#include <iostream>

Combination::Combination(QObject *parent) :
    QObject{parent}
{
}

Combination::Combination(const Combination &another):
    cards_(another.cards_), combination_(another.combination_)
{
    combinationCards_.reserve(COMBINATION_SIZE);
}

Combination::Combination(const Card &firstCard, const Card &secondCard, QObject *parent)
    : QObject{parent}
{
    cards_.push_back(firstCard);
    cards_.push_back(secondCard);
    combinationCards_.push_back(firstCard);
    combinationCards_.push_back(secondCard);
    combination_ = Combinations::HighCard;
    combinationCards_.reserve(COMBINATION_SIZE);
}

void Combination::addCard(const Card &card)
{
    cards_.push_back(card);
//    updateCombination();
}

void Combination::updateCombination() // не работает сортировка
{

    QVector<quint64> nominals(NOMINALS_NUMBER);
    QVector<quint64> suits(SUITS_NUMBER);
    QVector<Nominal> kares;
    QVector<Nominal> sets;
    QVector<Nominal> pairs;
    QVector<QPair<Nominal, Nominal>> fullHouse;
    Card ten(0, 8);
    Card jack(2, 9);
    std::sort(cards_.begin(), cards_.end());
    for (qint64 i = 0; i < cards_.size(); ++i){
       ++nominals[(quint64) cards_[i].nominal() - 2];
       ++suits[(quint64)cards_[i].suit()];
        std::cout << cards_[i] << std::endl;
    }
    // ищем стриты и флэши:
    QVector<Nominal> straights; // стартовый номинал стрита
    straights = checkStraight(nominals);
    for (const auto &nominal: straights){
        std::cout << "Straight: " << (qint32) nominal << std::endl;
    }
    QVector<Suit> flushs; // масть флэша
    flushs = checkFlush(suits);
    for (const auto &suit: flushs){
        std::cout << "FLush: " << (qint32) (suit) << std::endl;
    }
    bool hasStraights = straights.size() > 0;
    bool hasFlush = flushs.size() > 0;
    std::cout << "HAS STRAIGHTS: " << (quint32) hasStraights << " HAS FLUSH: " << (quint32) hasFlush << std::endl;
    bool hasStraightFlush = false;
    QVector<Nominal> straightFlushs = checkStraightFlush(cards_, straights, flushs);
    hasStraightFlush = straightFlushs.size() > 0;
    std::cout << "HAS STRAIGHT FLUSH: " << (quint64) hasStraightFlush << std::endl;

    // попытаемся выбрать максимальную комбинацию
    if (hasStraightFlush){ // стрит флэш / флэш рояль
        for (const auto &nominal: straightFlushs){
            if (nominal == Nominal::Ten){
                combination_ = Combinations::RoyalFlush;
                break;
            }
            combination_ = Combinations::StraightFlush; // nominal + 4 - старшая карта стрита
        }
    } else {
        kares = checkFourOfAKind(nominals);
        if (kares.size() > 0){
            combination_ = Combinations::FourOfAKind;
        } else{
            pairs = checkPairs(nominals);
            sets = checkSets(nominals);
            fullHouse = checkFullHouse(sets, pairs);
            bool hasPairs = pairs.size() >= 2;
            bool hasPair = pairs.size() > 0;
            bool hasSets = sets.size() > 0;
            bool hasFullHouse = fullHouse.size() > 0;
            if (hasFullHouse){
                combination_ = Combinations::FullHouse;
            } else if (hasFlush){
                combination_ = Combinations::Flush;
            } else if (hasStraights){
                combination_ = Combinations::Straight;
            } else if (hasSets){
                combination_ = Combinations::ThreeOfAKind;
            } else if (hasPairs){
                combination_ = Combinations::TwoPairs;
            } else if (hasPair){
                combination_ = Combinations::Pair;
            } else{
                combination_ = Combinations::HighCard;
            }
        }
    }
    std::cout << "COMBINATION: " << (quint64) combination_ << std::endl;

    // теперь составим комбинацию (во многом повторение прошлых действий, но что поделать...( )
    switch (combination_){
    case Combinations::HighCard:{
        fillHightCard();
        break;
    }
    case Combinations::Pair:{
        fillPair(pairs);
        break;
    }
    case Combinations::TwoPairs:{
        fillTwoPairs(pairs);
        break;
    }
    case Combinations::ThreeOfAKind:{
        fillSet(sets);
        break;
    }
    case Combinations::Straight:{
        fillStraight();
        break;
    }
    case Combinations::Flush:{
        fillFlush();
        break;
    }
    case Combinations::FullHouse:{
        fillFullHouse();
        break;
    }
    case Combinations::FourOfAKind:{
        fillFour();
        break;
    }
    case Combinations::StraightFlush:{
        fillStraightFlush();
        break;
    }
    case Combinations::RoyalFlush:{
        fillStraightFlush();
    }
    }
}

QVector<Suit> Combination::checkFlush(const QVector<quint64> &suits)
{
    QVector<Suit> flushs;
    Card card(0, 0);
    for (int i = 0; i < suits.size(); ++i){
        if (suits[i] >= COMBINATION_SIZE){
            card.setSuit(i);
            flushs.push_back(card.suit());
        }
    }
    return flushs;
}

QVector<Nominal> Combination::checkStraight(const QVector<quint64> &nominals)
{
    // в тупую пройдемся по всевозможным стартовым номиналам
    QVector<Nominal> straights;
    Card card(0, 0);
    for (qint32 start = (qint32) Nominal::Two - 2; start < (qint32) Nominal::Ace - 2; ++start){
        if (nominals[start] != 0 and (start <= (qint32) Nominal::Ten - 2 or start == (qint32) Nominal::Ace - 2)){
            qint32 next = (start == (qint32) Nominal::Ace - 2) ? (qint32) Nominal::Two - 2 : start + 1; // следующая карта в возможном стрите
            int lenght = 1; // длина текущей последовательности идущих подряд карт
            for (; lenght < 5; ++lenght, ++next){
                if (nominals[next] == 0){
                    break;
                }
            }
//            std::cout << "Lenght = " << lenght <<  " Next = " << next << std::endl;
            if (lenght == 5){
                card.setNominal(start + 2);
                straights.push_back(card.nominal());
            }
        }
    }
    return straights;
}

QVector<Nominal> Combination::checkPairs(const QVector<quint64> &nominals)
{
    QVector<Nominal> pairs;
    Card card(0, 0);
    for (quint64 i = 0; i < (quint64) nominals.size(); ++i){
        if (nominals[i] >= 2){
            card.setNominal(i + 2);
            pairs.push_back(card.nominal());
        }
    }
    return pairs;
}

QVector<Nominal> Combination::checkSets(const QVector<quint64> &nominals)
{
    QVector<Nominal> sets;
    Card card(0, 0);
    for (quint64 i = 0; i < (quint64) nominals.size(); ++i){
        if (nominals[i] >= 3){
            card.setNominal(i + 2);
            sets.push_back(card.nominal());
        }
    }
    return sets;
}

void Combination::fillStraightFlush()
{

}

void Combination::fillFour()
{

}

void Combination::fillFullHouse()
{

}

void Combination::fillFlush()
{

}

void Combination::fillStraight()
{

}

void Combination::fillSet(const QVector<Nominal> &sets)
{
    combinationCards_.clear();
    Nominal setNominal = *std::max_element(sets.begin(), sets.end());
    for (const auto &card: cards_){
        if (card.nominal() == setNominal){
            combinationCards_.push_back(card);
        }
    }
    auto k = qMin(COMBINATION_SIZE, (quint64) cards_.size()) - 3;
    for (int i = cards_.size() - 1; k > 0; --i){
        Card card = cards_[i];
        if (card.nominal() != setNominal){
            --k;
            combinationCards_.push_back(card);
        }
    }
}

void Combination::fillTwoPairs(const QVector<Nominal> &pairs)
{
    combinationCards_.clear();
    //сначала старшую пару
    Nominal firstNominal = pairs[0], secondNominal = pairs[1];
    if (firstNominal < secondNominal){
        std::swap(firstNominal, secondNominal);
    }
    for (int i = cards_.size() - 1; i >= 0; --i){ // обратный потому что firstNominal встретится раньше в виду отсортированности карт
        Card card = cards_[i];
        if (card.nominal() == firstNominal or card.nominal() == secondNominal){
            combinationCards_.push_back(card);
        }
    }
    auto k = qMin(COMBINATION_SIZE, (quint64) cards_.size()) - 4;
    for (int i = 0; k > 0; ++i){
        Card card = cards_[cards_.size() - 1 - i];
        if (card.nominal() != firstNominal and card.nominal() != secondNominal){
            --k;
            combinationCards_.push_back(card);
        }
    }
}

void Combination::fillPair(const QVector<Nominal> &pairs)
{
    // добавляем сначала пару для удобства сравнения
    Nominal pairNominal = pairs[0]; // опасное место
    combinationCards_.clear();
    for (const auto &card: cards_){
        if (card.nominal() == pairNominal){
            combinationCards_.push_back(card);
        }
    }
    auto k = qMin(COMBINATION_SIZE, (quint64) cards_.size()) - 2; // две карты типа добавили уже
    for (int i = 0; k > 0; ++i){
        Card card = cards_[cards_.size() - 1 - i];
        if (card.nominal() != pairNominal){
            --k;
            combinationCards_.push_back(card);
        }
    }
}

void Combination::fillHightCard()
{
    combinationCards_.clear();
    if (cards_.size() <= (int) COMBINATION_SIZE){
        combinationCards_ = cards_;
        return;
    }
    for (quint64 i = 0; i < COMBINATION_SIZE; ++i){
        combinationCards_[i] = cards_[cards_.size() - 1 - i]; // составляем комбинацию в порядке убывания
    }
}


QVector<Nominal> Combination::checkStraightFlush(const QVector<Card> &cards, const QVector<Nominal> &straights, const QVector<Suit> &flushs) // робит
{
    QVector<Nominal> straightFlushs;
    for (auto &nominal: straights){
        quint64 nom = (quint64) nominal;
        for (int i = 0; i < cards.size(); ++i){
            if ((quint64) cards[i].nominal() == nom){
                if (flushs.contains(cards[i].suit())){
                    int start = i;
                    bool isStraightFlush = true;
                    const Suit suit = cards[start].suit();
                    const Nominal startNominal = cards[start].nominal();
                    QVector<bool> checked(COMBINATION_SIZE, false);
                    checked[0] = true;
                    for (quint64 i = start + 1; i < (quint64) cards.size(); ++i){
                        if ((quint64) cards[i].nominal() >= (quint64) startNominal + COMBINATION_SIZE){
                            break;
                        }
                        quint64 ind = (quint64) cards[i].nominal() - (quint64) startNominal;
                        if (!checked[ind] and cards[i].suit() == suit){
                            checked[ind] = true;
                        }
                    }
                    for (auto &ok: checked){
                        isStraightFlush = isStraightFlush and ok;
                    }
                    if (isStraightFlush){
                        straightFlushs.push_back(nominal);
                    }
                }
            }
        }
    }
    return straightFlushs;
}

QVector<Nominal> Combination::checkFourOfAKind(const QVector<quint64> &nominals) // робит
{
    QVector<Nominal> ans;
    quint64 ansNominal = 0;
    for (quint64 i = 0; i < (quint64) nominals.size(); ++i){
        if (nominals[i] == SUITS_NUMBER){
            ansNominal = qMax(ansNominal, i + 2);
        }
    }
    if (ansNominal != 0){
        Card card(0, ansNominal);
        ans.push_back(card.nominal());
    }
    return ans;
}

QVector<QPair<Nominal, Nominal> > Combination::checkFullHouse(const QVector<Nominal> &sets, const QVector<Nominal> &pairs) // хз робит или нет
{
    QVector<QPair<Nominal, Nominal>> fullHouse;
    bool hasSets = sets.size() > 0, hasPairs = pairs.size() > 0;
    if (hasSets and hasPairs){
        Nominal maxSetNominal = *std::max_element(sets.begin(), sets.end());
        Nominal maxPairNominal = Nominal::Wrong;
        for (const auto &pairNominal: pairs){
            if (pairNominal > maxPairNominal and pairNominal != maxSetNominal){
                maxPairNominal = pairNominal;
            }
        }
        if (maxPairNominal != Nominal::Wrong){
            fullHouse.push_back(QPair<Nominal, Nominal>(maxSetNominal, maxPairNominal));
            std::cout << "FULL HOUSE: SET NOMINAL: " << (int) maxSetNominal << " : PAIR NOMINAL: " << (int) maxPairNominal << std::endl;
        }
    }
    return fullHouse;
}

std::ostream &operator<<(std::ostream &os, const Combination &comb){
    std::string combination;
    switch (comb.combination_){
    case Combinations::HighCard:{
        combination = "Hight Card";
        break;
    }
    case Combinations::Pair:{
        combination = "Pair";
        break;
    }
    case Combinations::TwoPairs:{
        combination = "Two Pairs";
        break;
    }
    case Combinations::ThreeOfAKind:{
        combination = "Set";
        break;
    }
    case Combinations::Straight:{
        combination = "Straight";
        break;
    }
    case Combinations::Flush:{
        combination = "Flush";
        break;
    }
    case Combinations::FullHouse:{
        combination = "Full house";
        break;
    }
    case Combinations::FourOfAKind:{
        combination = "Kare";
        break;
    }
    case Combinations::StraightFlush:{
        combination = "Straight Flush";
        break;
    }
    case Combinations::RoyalFlush:{
        combination = "Flush Royal";
    }
    }
    os << combination << std::endl;
    for (const auto &card: comb.combinationCards_){
        os << card << std::endl;
    }
    return os;
}

