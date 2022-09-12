#include "combination.h"

#include <QMap>
#include <algorithm>
#include <iostream>

Combination::Combination(QObject *parent)
    : QObject{parent}, combination_(Combinations::Error) {}

Combination::Combination(const Combination &another) : QObject() {
  combinationCards_.reserve(COMBINATION_SIZE);
  cards_.reserve(COMBINATION_SIZE + 2);
  cards_ = another.cards_;
  combinationCards_ = another.combinationCards_;
  combination_ = another.combination_;
}

Combination::Combination(const Card &firstCard, const Card &secondCard,
                         QObject *parent)
    : QObject{parent} {
  cards_.reserve(COMBINATION_SIZE + 2);
  combinationCards_.reserve(COMBINATION_SIZE);
  cards_.push_back(firstCard);
  cards_.push_back(secondCard);

  updateCombination();
}

/*!
 * \brief Добавляет карту в комбинацию
 * \param card - карта, которую необходимо добавить
 */
void Combination::addCard(const Card &card) {
  cards_.push_back(card);
  updateCombination();
}

void Combination::updateCombination() {

  QVector<quint64> nominals(NOMINALS_NUMBER);
  QVector<quint64> suits(SUITS_NUMBER);
  QVector<Nominal> kares;
  QVector<Nominal> sets;
  QVector<Nominal> pairs;
  QVector<QPair<Nominal, Nominal>> fullHouse;
  Card ten(0, 8);
  Card jack(2, 9);
  std::sort(cards_.begin(), cards_.end());
  for (qint64 i = 0; i < cards_.size(); ++i) {
    ++nominals[(quint64)cards_[i].nominal() - 2];
    ++suits[(quint64)cards_[i].suit()];
    //    std::cout << cards_[i] << std::endl;
  }
  //  std::cout << std::endl;
  // ищем стриты и флэши:
  QVector<Nominal> straights; // стартовый номинал стрита
  straights = checkStraight(nominals);
  //  for (const auto &nominal : straights) {
  //    std::cout << "Straight: " << (qint32)nominal << std::endl;
  //  }
  QVector<Suit> flushs; // масть флэша
  flushs = checkFlush(suits);
  //  for (const auto &suit : flushs) {
  //    std::cout << "FLush: " << (qint32)(suit) << std::endl;
  //  }
  bool hasStraights = straights.size() > 0;
  bool hasFlush = flushs.size() > 0;
  //  std::cout << "HAS STRAIGHTS: " << (quint32)hasStraights
  //            << " HAS FLUSH: " << (quint32)hasFlush << std::endl;
  bool hasStraightFlush = false;
  QVector<QPair<Nominal, Suit>> straightFlushs =
      checkStraightFlush(cards_, straights, flushs);
  hasStraightFlush = straightFlushs.size() > 0;
  //  std::cout << "HAS STRAIGHT FLUSH: " << (quint64)hasStraightFlush <<
  //  std::endl;

  // попытаемся выбрать максимальную комбинацию
  if (hasStraightFlush) { // стрит флэш / флэш рояль
    for (const auto &pair : straightFlushs) {
      if (pair.first == Nominal::Ten) {
        combination_ = Combinations::RoyalFlush;
        break;
      }
      combination_ =
          Combinations::StraightFlush; // nominal + 4 - старшая карта стрита
    }
  } else {
    kares = checkFourOfAKind(nominals);
    if (kares.size() > 0) {
      combination_ = Combinations::FourOfAKind;
    } else {
      pairs = checkPairs(nominals);
      sets = checkSets(nominals);
      fullHouse = checkFullHouse(sets, pairs);
      bool hasPairs = pairs.size() >= 2;
      bool hasPair = pairs.size() > 0;
      bool hasSets = sets.size() > 0;
      bool hasFullHouse = fullHouse.size() > 0;
      if (hasFullHouse) {
        combination_ = Combinations::FullHouse;
      } else if (hasFlush) {
        combination_ = Combinations::Flush;
      } else if (hasStraights) {
        combination_ = Combinations::Straight;
      } else if (hasSets) {
        combination_ = Combinations::ThreeOfAKind;
      } else if (hasPairs) {
        combination_ = Combinations::TwoPairs;
      } else if (hasPair) {
        combination_ = Combinations::Pair;
      } else {
        combination_ = Combinations::HighCard;
      }
    }
  }
  //  std::cout << "COMBINATION: " << (quint64)combination_ << std::endl;

  // теперь составим комбинацию (во многом повторение прошлых действий, но что
  // поделать...( )
  combinationCards_.clear();
  switch (combination_) {
  case Combinations::HighCard: {
    fillHighCard();
    break;
  }
  case Combinations::Pair: {
    fillPair(pairs);
    break;
  }
  case Combinations::TwoPairs: {
    fillTwoPairs(pairs);
    break;
  }
  case Combinations::ThreeOfAKind: {
    fillSet(sets);
    break;
  }
  case Combinations::Straight: {
    fillStraight(straights);
    break;
  }
  case Combinations::Flush: {
    fillFlush(flushs);
    break;
  }
  case Combinations::FullHouse: {
    fillFullHouse(fullHouse);
    break;
  }
  case Combinations::FourOfAKind: {
    fillFour(kares);
    break;
  }
  case Combinations::StraightFlush: {
    fillStraightFlush(straightFlushs);
    break;
  }
  case Combinations::RoyalFlush: {
    fillStraightFlush(straightFlushs);
  }
  case Combinations::Error: {
  }
  }
  //  std::cout << std::endl;
}

/*!
 * \brief Оператор присваивания
 */
Combination &Combination::operator=(const Combination &another) {
  cards_ = another.cards_;
  combinationCards_ = another.combinationCards_;
  combination_ = another.combination_;
  return *this;
}

/*!
 * \brief Функция, определяющая флэши
 * \param suits - вектор, в i-ом элементе которого содержится количество карт,
 * имеющих i-ую масть \return вектор, содержащий масти флэшей
 */
QVector<Suit> Combination::checkFlush(const QVector<quint64> &suits) {
  QVector<Suit> flushs;
  Card card(0, 0);
  for (int i = 0; i < suits.size(); ++i) {
    if (suits[i] >= COMBINATION_SIZE) {
      card.setSuit(i);
      flushs.push_back(card.suit());
    }
  }
  return flushs;
}

QVector<Nominal> Combination::checkStraight(const QVector<quint64> &nominals) {
  // в тупую пройдемся по всевозможным стартовым номиналам
  QVector<Nominal> straights;
  Card card(0, 0);
  for (qint32 start = (qint32)Nominal::Two - 2;
       start <= (qint32)Nominal::Ace - 2; ++start) {
    if (nominals[start] != 0 and (start <= (qint32)Nominal::Ten - 2 or
                                  start == (qint32)Nominal::Ace - 2)) {
      qint32 next = (start == (qint32)Nominal::Ace - 2)
                        ? (qint32)Nominal::Two - 2
                        : start + 1; // следующая карта в возможном стрите
      int lenght = 1; // длина текущей последовательности идущих подряд карт
      for (; lenght < 5; ++lenght, ++next) {
        if (nominals[next] == 0) {
          break;
        }
      }
      //            std::cout << "Lenght = " << lenght <<  " Next = " << next <<
      //            std::endl;
      if (lenght == 5) {
        card.setNominal(start + 2);
        straights.push_back(card.nominal());
      }
    }
  }
  return straights;
}

/*!
 * \brief функция проверки пар
 * \param nominals - вектор, в i-й позиции которого количество карт с i-м
 * номиналом \return вектор, содержащий номиналы пар
 */
QVector<Nominal> Combination::checkPairs(const QVector<quint64> &nominals) {
  QVector<Nominal> pairs;
  Card card(0, 0);
  for (quint64 i = 0; i < (quint64)nominals.size(); ++i) {
    if (nominals[i] >= 2) {
      card.setNominal(i + 2);
      pairs.push_back(card.nominal());
    }
  }
  return pairs;
}

/*!
 * \brief Функция проверки сетов
 * \param nominals - вектор, в i-й позиции которого количество карт с i-м
 * номиналом \return вектор, содержащий номиналы сетов
 */
QVector<Nominal> Combination::checkSets(const QVector<quint64> &nominals) {
  QVector<Nominal> sets;
  Card card(0, 0);
  for (quint64 i = 0; i < (quint64)nominals.size(); ++i) {
    if (nominals[i] >= 3) {
      card.setNominal(i + 2);
      sets.push_back(card.nominal());
    }
  }
  return sets;
}

/*!
 * \brief Функция заполняет комбинацию стрит флэша
 * \param straightflush - вектор, содержащий номинал начала и масть стрит флэша
 */
void Combination::fillStraightFlush(
    const QVector<QPair<Nominal, Suit>> &straightflush) {
  Card card;
  Nominal nominal = straightflush[0].first;
  Suit suit = straightflush[0].second;
  card.setSuit((quint64)suit);
  for (int i = COMBINATION_SIZE - 1; i >= 0; --i) {
    card.setNominal((quint64)nominal + i);
    combinationCards_.push_back(card);
  }
}

/*!
 * \brief Функция заполняет комбинацию каре
 * \param kare - вектор, содержащий номиналы каре
 */
void Combination::fillFour(
    const QVector<Nominal> &kare) { // каре может быть только одно
  Nominal nominal = kare[0];
  combinationCards_.append(QVector<Card>{
      Card(3, (quint64)nominal - 2), Card(2, (quint64)nominal - 2),
      Card(1, (quint64)nominal - 2), Card(0, (quint64)nominal - 2)});
  for (int i = cards_.size() - 1; i >= 0; --i) {
    if (cards_[i].nominal() != nominal) {
      combinationCards_.push_back(cards_[i]);
      break;
    }
  }
}

/*!
 * \brief функция заполняет комбинацию фулл хауса
 * \param fullHouse - вектор, содержащий номиналы сета и пары для фулл хауса
 */
void Combination::fillFullHouse(
    const QVector<QPair<Nominal, Nominal>> &fullHouse) {
  combinationCards_.resize(COMBINATION_SIZE);
  Nominal setNominal = fullHouse[0].first;
  Nominal pairNominal = fullHouse[0].second;
  int curSet = 0;
  int curPair = 0;
  //  std::cout << (int)setNominal << " " << (int)pairNominal << std::endl;
  for (int i = cards_.size() - 1; i >= 0 and (curSet < 3 or curPair < 2); --i) {
    //    std::cout << "CUR INDEX: " << i << std::endl;
    if (curSet < 3 and cards_[i].nominal() == setNominal) {
      //      std::cout << curSet << std::endl;
      combinationCards_[curSet] = cards_[i];
      ++curSet;
    }
    if (curPair < 2 and cards_[i].nominal() == pairNominal) {
      //      std::cout << "INDEX PAIR: " << 5 - curPair << std::endl;
      combinationCards_[3 + curPair] = cards_[i];
      ++curPair;
    }
  }
}

/*!
 * \brief функция заполняет комбинацию флэша
 * \param flushs - вектор, содержащий масти флэша
 */
void Combination::fillFlush(const QVector<Suit> &flushs) {
  // если и есть флэш, то он только один
  Suit suit = flushs[0];
  int cur = COMBINATION_SIZE; // сколько осталось положить карт в комбинацию
  for (int i = cards_.size() - 1; i >= 0 and cur > 0; --i) {
    if (cards_[i].suit() == suit) {
      --cur;
      combinationCards_.push_back(cards_[i]);
    }
  }
}

void Combination::fillStraight(const QVector<Nominal> &straights) {
  Nominal maxNominal = Nominal::Wrong;
  for (const auto &nom : straights) {
    if ((nom > maxNominal) or (maxNominal == Nominal::Ace)) {
      maxNominal = nom;
    }
  }
  // нашли стартовый номинал, теперь составляем кобинацию
  int cur = 4;
  if (maxNominal == Nominal::Ace) {
    --cur;
    maxNominal = Nominal::Two;
    combinationCards_.push_back(
        cards_.last()); // если есть туз в руке => он последний 100% если
    // несколько тузов => похер какой, ибо стрит
  }
  for (int i = cards_.size() - 1; i >= 0 and cur >= 0; --i) {
    if ((quint64)cards_[i].nominal() == (quint64)maxNominal + cur) {
      --cur;
      combinationCards_.push_back(cards_[i]);
    }
  }
}

/*!
 * \brief Функция заполняет комбинацию сета
 * \param sets - вектор, содержащий номиналы сетов
 */
void Combination::fillSet(const QVector<Nominal> &sets) {
  Nominal setNominal = *std::max_element(sets.begin(), sets.end());
  for (const auto &card : cards_) {
    if (card.nominal() == setNominal) {
      combinationCards_.push_back(card);
    }
  }
  auto k = qMin(COMBINATION_SIZE, (quint64)cards_.size()) - 3;
  for (int i = cards_.size() - 1; k > 0; --i) {
    Card card = cards_[i];
    if (card.nominal() != setNominal) {
      --k;
      combinationCards_.push_back(card);
    }
  }
}

/*!
 * \brief Функция заполняет комбинацию двух пар
 * \param pairs - вектор, содержащий номиналы пар
 */
void Combination::fillTwoPairs(const QVector<Nominal> &pairs) {
  // сначала старшую пару
  Nominal firstNominal = pairs[0], secondNominal = pairs[1];
  if (firstNominal < secondNominal) {
    std::swap(firstNominal, secondNominal);
  }
  for (int i = cards_.size() - 1; i >= 0;
       --i) { // обратный потому что firstNominal встретится раньше в виду
    // отсортированности карт
    Card card = cards_[i];
    if (card.nominal() == firstNominal or card.nominal() == secondNominal) {
      combinationCards_.push_back(card);
    }
  }
  auto k = qMin(COMBINATION_SIZE, (quint64)cards_.size()) - 4;
  for (int i = 0; k > 0; ++i) {
    Card card = cards_[cards_.size() - 1 - i];
    if (card.nominal() != firstNominal and card.nominal() != secondNominal) {
      --k;
      combinationCards_.push_back(card);
    }
  }
}

/*!
 * \brief функция заполняет комбинацию пары
 * \param pairs - вектор, содержащий номиналы пар
 */
void Combination::fillPair(const QVector<Nominal> &pairs) {
  // добавляем сначала пару для удобства сравнения
  Nominal pairNominal = pairs[0]; // опасное место
  for (const auto &card : cards_) {
    if (card.nominal() == pairNominal) {
      combinationCards_.push_back(card);
    }
  }
  auto k = qMin(COMBINATION_SIZE, (quint64)cards_.size()) -
           2; // две карты типа добавили уже
  for (int i = 0; k > 0; ++i) {
    Card card = cards_[cards_.size() - 1 - i];
    if (card.nominal() != pairNominal) {
      --k;
      combinationCards_.push_back(card);
    }
  }
}

/*!
 * \brief заполняет комбинациию старшей карты
 */
void Combination::fillHighCard() {
  if (cards_.size() <= (int)COMBINATION_SIZE) {
    combinationCards_ = cards_;
    return;
  }
  int cur = 5;
  for (int i = cards_.size() - 1; i >= 0 and cur > 0;
       --i, --cur) { // тупо перетаскиваем первые 5 максимальных элементов
    combinationCards_.push_back(cards_[i]);
  }
}

/*!
 * \brief Функция проверки на стрит-флэш
 * \param cards - рука (вектор карт, находящихся на руке)
 * \param straights - вектор, в котором содержатся номиналы стритов
 * \param flushs - вектор, в котором содержатся масти флэшей
 * \return вектор пар <Nominal, Suit>, определяющих стрит-флэш. Nominal -
 * номинал начало стрит флэша
 */
QVector<QPair<Nominal, Suit>>
Combination::checkStraightFlush(const QVector<Card> &cards,
                                const QVector<Nominal> &straights,
                                const QVector<Suit> &flushs) // робит
{
  //    QVector<Nominal> straightFlushs;
  QVector<QPair<Nominal, Suit>> maxStraightFlush;
  maxStraightFlush.reserve(1);
  Nominal maxNominal = Nominal::Wrong;
  for (auto &nominal : straights) {
    if (nominal < maxNominal) {
      continue;
    }
    quint64 nom = (quint64)nominal;
    for (int i = 0; i < cards.size(); ++i) {
      if ((quint64)cards[i].nominal() == nom) {
        if (flushs.contains(cards[i].suit())) {
          int start = i;
          bool isStraightFlush = true;
          const Suit suit = cards[start].suit();
          const Nominal startNominal = cards[start].nominal();
          QVector<bool> checked(COMBINATION_SIZE, false);
          checked[0] = true;
          for (quint64 i = start + 1; i < (quint64)cards.size(); ++i) {
            if ((quint64)cards[i].nominal() >=
                (quint64)startNominal + COMBINATION_SIZE) {
              break;
            }
            quint64 ind = (quint64)cards[i].nominal() - (quint64)startNominal;
            if (!checked[ind] and cards[i].suit() == suit) {
              checked[ind] = true;
            }
          }
          for (auto &ok : checked) {
            isStraightFlush = isStraightFlush and ok;
          }
          if (isStraightFlush) {
            // straightFlushs.push_back(nominal);
            auto pair = QPair(nominal, suit);
            if (maxStraightFlush.size() != 0) {
              maxStraightFlush[0] = pair;
            } else {
              maxStraightFlush.push_back(pair);
            }
          }
        }
      }
    }
  }
  return maxStraightFlush;
}

/*!
 * \brief функция проверки на каре
 * \param nominals - вектор номиналов. В i-м позиции лежит количество i-х
 * номиналов в руке \return вектор, в котором лежат номиналы каре
 */
QVector<Nominal>
Combination::checkFourOfAKind(const QVector<quint64> &nominals) // робит
{
  QVector<Nominal> ans;
  quint64 ansNominal = 0;
  for (int i = 0; i < nominals.size(); ++i) {
    if (nominals[i] == SUITS_NUMBER) {
      ansNominal = qMax(ansNominal, (quint64)i);
    }
  }
  if (ansNominal != 0) {
    Card card(0, ansNominal);
    ans.push_back(card.nominal());
  }
  return ans;
}

/*!
 * \brief Функция проверки на FullHouse
 * \param sets - вектор из номиналов сетов
 * \param pairs - вектор из номиналов пар
 * \return вектор пар <set, pair>, определяющих фулл хаус
 */
QVector<QPair<Nominal, Nominal>>
Combination::checkFullHouse(const QVector<Nominal> &sets,
                            const QVector<Nominal> &pairs) {
  QVector<QPair<Nominal, Nominal>> fullHouse;
  bool hasSets = sets.size() > 0, hasPairs = pairs.size() > 0;
  if (hasSets and hasPairs) {
    Nominal maxSetNominal = *std::max_element(sets.begin(), sets.end());
    Nominal maxPairNominal = Nominal::Wrong;
    for (const auto &pairNominal : pairs) {
      if (pairNominal > maxPairNominal and pairNominal != maxSetNominal) {
        maxPairNominal = pairNominal;
      }
    }
    if (maxPairNominal != Nominal::Wrong) {
      fullHouse.push_back(
          QPair<Nominal, Nominal>(maxSetNominal, maxPairNominal));
      //      std::cout << "FULL HOUSE: SET NOMINAL: " << (int)maxSetNominal
      //                << " : PAIR NOMINAL: " << (int)maxPairNominal <<
      //                std::endl;
    }
  }
  return fullHouse;
}

/*!
 * \brief оператор вывода. Выводит комбинацию и карты, входящие в нее
 */
std::ostream &operator<<(std::ostream &os, const Combination &comb) {
  std::string combination;
  switch (comb.combination_) {
  case Combinations::HighCard: {
    combination = "Hight Card";
    break;
  }
  case Combinations::Pair: {
    combination = "Pair";
    break;
  }
  case Combinations::TwoPairs: {
    combination = "Two Pairs";
    break;
  }
  case Combinations::ThreeOfAKind: {
    combination = "Set";
    break;
  }
  case Combinations::Straight: {
    combination = "Straight";
    break;
  }
  case Combinations::Flush: {
    combination = "Flush";
    break;
  }
  case Combinations::FullHouse: {
    combination = "Full house";
    break;
  }
  case Combinations::FourOfAKind: {
    combination = "Kare";
    break;
  }
  case Combinations::StraightFlush: {
    combination = "Straight Flush";
    break;
  }
  case Combinations::RoyalFlush: {
    combination = "Flush Royal";
    break;
  }
  case Combinations::Error: {
    combination = "ERROR";
  }
  }
  os << combination << std::endl;
  for (const auto &card : comb.combinationCards_) {
    os << card << std::endl;
  }
  return os;
}

/*!
 * \brief Оператор меньше
 * \return true, если левая комбинация меньше, false - в остальных случаях
 */
bool operator<(const Combination &left, const Combination &right) {
  if (left.combination_ != right.combination_) {
    return left.combination_ < right.combination_;
  }
  if (left.combinationCards_.size() != right.combinationCards_.size()) {
    return left.combinationCards_.size() < right.combinationCards_.size();
  }
  for (int i = 0; i < left.combinationCards_.size(); ++i) {
    Nominal leftNom = left.combinationCards_[i].nominal();
    Nominal rightNom = right.combinationCards_[i].nominal();
    if (leftNom != rightNom) {
      return leftNom < rightNom;
    }
  }
  // в случае, если полностью одинаковые комбинации
  return false;
}

/*!
 * \brief оператор больше
 * \return true, если левая комбинация больше
 */
bool operator>(const Combination &left, const Combination &right) {
  return !(left < right or left == right);
}

/*!
 * \brief оператор сравнения
 * \return true, если комбинации равны. false - в остальных случаях
 */
bool operator==(const Combination &left, const Combination &right) {
  if (left.combination_ != right.combination_) {
    return false;
  }
  if (left.combinationCards_.size() != right.combinationCards_.size()) {
    return false;
  }
  for (int i = 0; i < left.combinationCards_.size(); ++i) {
    Nominal leftNom = left.combinationCards_[i].nominal();
    Nominal rightNom = right.combinationCards_[i].nominal();
    if (leftNom != rightNom) {
      return false;
    }
  }
  // в случае, если полностью одинаковые комбинации
  return true;
}

Combinations Combination::combination() const { return combination_; }
int Combination::size() { return cards_.size(); }
