#ifndef TABLE_H
#define TABLE_H

#include "player.h"
#include <QObject>
#include <QRandomGenerator>

// TODO: переделать все в указатели
class Table : public QObject {
Q_OBJECT
public:
    explicit Table(const QString &name, const char &size,
                   QObject *parente = nullptr);

    QString name() const;

    QVector<Player *> players() const;

    void giveCardToPlayer(const QString &playerName);

    void putCardOnTable();

    void addPlayer(const QString &playerName, const qint64 &id, const quint64 &seat);

    int size() const;

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
    QVector<Player *> players_;
    QVector<Player *> gamePlayers_;
    QVector<Card> tableCards_;
    QVector<bool> usedCards_;
    QRandomGenerator generator_;
    quint32 curBet_;
    int size_;
    Combination winnerComb_;
    quint32 bank_;
};

#endif // TABLE_H
