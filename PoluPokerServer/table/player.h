#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QTcpSocket>

#include "combination.h"

const quint64 DEFAULT_COINS = 10000;

class Player : public QObject {
 Q_OBJECT
 public:
  Player();

  Player(const QString &name, QTcpSocket *sock, const int &seat,
		 QObject *parent = nullptr);

  Player(const Player &another);

  [[nodiscard]] QString name() const;

  [[nodiscard]] Combination combination() const;

  void addCard(const Card &card);

  Player &operator=(const Player &player);

  friend std::ostream &operator<<(std::ostream &os, const Player &player);

  friend bool operator<(const Player &left, const Player &right);

  [[nodiscard]] int seat() const;
  void setSeat(int seat);

  [[nodiscard]] int coins() const;
  void setCoins(int coins);

  [[nodiscard]] QTcpSocket *socket() const;
  void setSocket(QTcpSocket *socket);
 private:
  QString name_;
  QTcpSocket *socket_;
  int coins_;
  int seat_;
  Combination combination_;
};

#endif // PLAYER_H
