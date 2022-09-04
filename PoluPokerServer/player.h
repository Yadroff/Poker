#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "combination.h"

const quint64 DEFAULT_COINS = 10000;

class Player : public QObject {
Q_OBJECT
public:
    Player();

    Player(const QString &name, const qint64 &id, const int &seat, QObject *parent = nullptr);

    Player(const Player &another);

    QString name() const;

    Combination combination() const;

    void addCard(const Card &card);

    Player &operator=(const Player &player);

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

    friend bool operator<(const Player &left, const Player &right);

private:
    QString name_;
    qint64 id_;
    quint64 coins_;
    int seat_;
    Combination combination_;
};

#endif // PLAYER_H
