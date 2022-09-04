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

    bool addPlayer(const QString &playerName, const qint64 &id, const quint64 &seat);

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
    QMap<QString, Player *> players_;
    QMap<QString, Player *> gamePlayers_;
    QVector<Card> tableCards_;
    QVector<bool> usedCards_;
    QRandomGenerator generator_;
    quint32 curBet_;
    int size_;
    Combination winnerComb_;
    quint32 bank_;
};

#endif // TABLE_H
