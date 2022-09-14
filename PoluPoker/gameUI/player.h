#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <gameUI/seat.h>
#include <gameUI/card.h>

const int DEFAULT_COINS = 5000;
class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(const QString &name, QObject *parent = nullptr);
    Player(const QString &name, Seat *seat);
    void giveCard(const QString &suit, const QString &nominal);
    void changeSeat(Seat *seat);
    void clearCards();

    int money() const;
    void bet(qint32 &bet);

private:
    Card card_;
    int cardsCount_;
    QString name_;
    qint32 money_;
    Seat *seat_;
public slots:
    void leaveTable();
};

#endif // PLAYER_H
