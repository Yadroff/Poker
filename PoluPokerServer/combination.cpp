#include "combination.h"

#include <QMap>
#include <QtAlgorithms>
#include <algorithm>
#include <iostream>

Combination::Combination(QObject *parent) :
    QObject{parent}
{

}

Combination::Combination(const Combination &another):
    cards_(another.cards_), combination_(another.combination_)
{

}

Combination::Combination(const Card &firstCard, const Card &secondCard, QObject *parent)
    : QObject{parent}
{
    cards_.push_back(firstCard);
    cards_.push_back(secondCard);
    combinationCards_.push_back(firstCard);
    combinationCards_.push_back(secondCard);
    combination_ = 0;
}

void Combination::addCard(const Card &card)
{
    cards_.push_back(card);
//    updateCombination();
}

void Combination::updateCombination()
{

    QMap<Nominal, quint64> nominalsMap;
    QMap<Suit, quint64> suitMap;
    QVector<QPair<Nominal, quint64>> straights; // <старт, длина>
    std::sort(cards_.begin(), cards_.end());
    for (qint64 i = 0; i < cards_.size(); ++i){
       ++nominalsMap[cards_[i].nominal()];
       ++suitMap[cards_[i].suit()];
    }
//    std::cout << "START: " << start << " COUNT: " << count << std::endl;
//    std::cout << "STRAIGHTS: " << straights.size() << std::endl;
//    for (quint64 i = start; i <  start + count; ++i){
//        std::cout << cards_[i] << "; ";
//    }
//    std::cout << std::endl;
    // ищем стриты и флэши:
    straights = checkStraight(nominalsMap);
    bool hasStraights = straights.size() > 0;
    bool hasFlush = checkFlush(suitMap);
    std::cout << "HAS STRAIGHTS: " << (quint32) hasStraights << " HAS FLUSH: " << (quint32) hasFlush << std::endl;
    bool hasStraightFlush = false;
    if (hasStraights and hasFlush){
        // мб стрит флэш
        for (auto &pair: straights){
            quint64 nom = (quint64) pair.first;
            quint64 len = pair.second;
            for (quint64 nominal = nom; (quint64) nominal + COMBINATION_SIZE <= nom + len; ++nominal){
                for (quint64 ind = 0; ind < cards_.size(); ++ind){
                    if ((quint64) cards_[ind].nominal() == nominal){
                        bool isFlushStraight = checkFlushStraight(ind, cards_);
                        if (isFlushStraight){
                            std::cout << "STRAIGHT FLUSH: " << cards_[ind] << std::endl;
                        }
                    }
                }
            }
        }
    }
//         ПЕРЕДЕЛАТЬ ПРОВЕРКУ НА СТРИТ-ФЛЭШ
    std::cout << "HAS STRAIGHT FLUSH: " << (quint64) hasStraightFlush << std::endl;
}

bool Combination::checkFlush(const QMap<Suit, quint64> &map)
{
    bool hasFlush = false;
    foreach(Suit suit, map.keys()){
        hasFlush = hasFlush or (map[suit] >= 5);
        if (hasFlush){
            break;
        }
    }
    return hasFlush;
}

QVector<QPair<Nominal, quint64> > Combination::checkStraight(const QMap<Nominal, quint64> &nominalsMap)
{
    QVector<QPair<Nominal, quint64>> straights;
    Nominal prev = nominalsMap.begin().key(), startCur = nominalsMap.begin().key();
    quint64 countCur = 1;
    for(auto it = nominalsMap.begin(); it != nominalsMap.end(); ++it){
        if (it != nominalsMap.begin() and (quint64) prev + 1 == (quint64) it.key()){
            ++countCur;
        } else{
            if (countCur >= 5){
                straights.push_back(QPair(startCur, countCur));
            }
            countCur = 1;
            startCur = it.key();
        }
        prev = it.key();
    }
    if (countCur >= 5){ // обновление в случае если последний элемент входит в комбинацию подряд идущих
        straights.push_back(QPair(startCur, countCur));
    }
    return straights;
}

bool Combination::checkFlushStraight(const quint64 &start, const QVector<Card> &cards_)
{
    bool isStraightFlush = true;
    const Suit suit = cards_[start].suit();
    const Nominal startNominal = cards_[start].nominal();
    QVector<bool> checked(COMBINATION_SIZE, false);
    checked[0] = true;
    for (quint64 i = start + 1; i < (quint64) cards_.size(); ++i){
        if ((quint64) cards_[i].nominal() >= (quint64) startNominal + COMBINATION_SIZE){
            break;
        }
        quint64 ind = (quint64) cards_[i].nominal() - (quint64) startNominal;
        if (!checked[ind] and cards_[i].suit() == suit){
            checked[ind] = true;
        }
    }
    for (auto &ok: checked){
        isStraightFlush = isStraightFlush and ok;
    }
    return isStraightFlush;
}


