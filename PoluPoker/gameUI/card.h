#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QPixmap>

const int xCardSize= 44;
const int yCardSize = 63;

enum class Suit {
    hearts = 0, // черви
    diamonds, // буби
    clubs, // крести
    spades, // пики
    closed, // закрытая
};

enum class Rank {
    ace = 0,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    closed
};

const int SUITS_NUMBER = 4;
const int NOMINALS_NUMBER = 13;

class Card : public QObject
{
    Q_OBJECT
public:
    explicit Card(QObject *parent = nullptr);
    void setCard(const QString &suit, const QString &nominal); // устанавливаем карту
    QPixmap getPixmap(); // возвращает QPixmap для дальнейшей отрисовки карты
private:
    const QPixmap cardDeck_;
    Rank rank_;
    Suit suit_;

};

#endif // CARD_H
