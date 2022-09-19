#ifndef TABLE_H
#define TABLE_H

#include "player.h"
#include <QObject>
#include <QRandomGenerator>
#include <QMap>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

// TODO: переделать вектор в мапу
class Table : public QObject {
Q_OBJECT
public:
    explicit Table(const QString &name, const char &size = 8,
                   QObject *parent = nullptr);

    [[nodiscard]] QString name() const;

    [[nodiscard]] QMap<QString, Player *> players() const;

    void giveCardToPlayer(Player *player);

    void putCardOnTable();

    bool addPlayer(const QString &playerName, QTcpSocket *socket, const int &seat);

    [[nodiscard]] int size() const;

    [[nodiscard]] int bet() const;

    [[nodiscard]] int pot() const;

	void playerFold(const Player &player);

	void sendToAll(const QByteArray &arr);

	static QJsonDocument sendChat(const QString &sender, const QString &message);

	void start();

	[[nodiscard]] bool isActive() const;

	void leavePlayer(const QString &playerName);
signals:
private:
    QVector<Player *> calculateWinner();

    Card generateCard();

    void blind();

    void flop();

    void tern();

    void river();

    void betting(const Player &player);

	void test();

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
	bool isActive_;
	const int MINIMAL_PLAYERS = 3;
};

#endif // TABLE_H