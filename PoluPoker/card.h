//#ifndef CARD_H
//#define CARD_H

//#include <QObject>
//#include <QPixmap>

//const qint32 xCardSize= 43;
//const qint32 yCardSize = 62;

//enum suit{
//    hearts = 0, // черви
//    diamonds = 1, // буби
//    clubs = 2, // крести
//    spades = 3 // пики
//};

//enum rank{
//    ace = 0,
//    two = 1,
//    three = 2,
//    four = 3,
//    five = 4,
//    six = 5,
//    seven = 6,
//    eight = 7,
//    nine = 8,
//    ten = 9,
//    jack = 10,
//    queen = 11,
//    king = 12
//};

//class Card : public QObject
//{
//    Q_OBJECT
//public:
//    explicit Card(QObject *parent = nullptr);
//    void setCard(suit _suit, rank _rank); // устанавливаем карту
//    QPixmap getPixmap(); // возвращает QPixmap для дальнейшей отрисовки карты
//private:
//    const QPixmap cardDeck_;
//    rank rank_;
//    suit suit_;

//};

//#endif // CARD_H
