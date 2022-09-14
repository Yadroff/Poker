#ifndef TABLE_H
#define TABLE_H

#include "player.h"
#include <QObject>
#include <QRandomGenerator>
#include <QMap>

// TODO: переделать вектор в мапу
class Table : public QObject {
Q_OBJECT
public:
    explicit Table(const QString &name, const char &size = 8,
                   QObject *parent = nullptr);

    QString name() const;

    QMap<QString, Player *> players() const;

    void giveCardToPlayer(const QString &playerName);

    void putCardOnTable();

    bool addPlayer(const QString &playerName, const int &id, const int &seat);

    int size() const;

    int bet() const;

    int pot() const;

signals:
private:
    QVector<Player *> calculateWinner();

    Card generateCard();

    void blind();

    void flop();

    void tern();

    void river();

    void betting(const int &start);

    QString name_;
    QMap<QString, Player *> players_;
    QMap<QString, Player *> gamePlayers_;
    QVector<Card> tableCards_;
    QVector<bool> usedCards_;
    QRandomGenerator generator_;
    int curBet_;
    int size_;
    Combination winnerComb_;
    int bank_;
};

#endif // TABLE_H