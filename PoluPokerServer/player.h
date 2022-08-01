#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "combination.h"

const quint64 DEFAULT_COINS = 10000;

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(const qint64 &id, const quint64 &seat, QObject *parent = nullptr);
    Player(const Player &another);
signals:
private:
    qint64 id_;
    quint64 coins_;
    quint64 seat_;
    Combination combination_;
};

#endif // PLAYER_H
