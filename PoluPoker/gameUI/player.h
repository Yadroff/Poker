#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <gameUI/seat.h>
#include <gameUI/card.h>

const int DEFAULT_COINS = 5000;
class Player : public QObject {
 Q_OBJECT
 public:
  explicit Player(const QString &name, QObject *parent = nullptr);
  Player(const QString &name, const int &money, Seat *seat);
  void giveCard(const QString &suit = "Closed", const QString &nominal = "Closed");
  void changeSeat(Seat *seat);
  void clearCards();

  [[nodiscard]] int money() const;
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
