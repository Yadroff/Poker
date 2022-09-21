#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include "gameUI/player.h"
#include "gameUI/seat.h"
namespace Ui {
class GameUI;
}

class GameUI : public QMainWindow {
 Q_OBJECT

 public:
  explicit GameUI(const QString &tableName, const QString &myName, const int &bet, const int &pot,
				  QWidget *parent = nullptr);
  void addPlayer(const QString &name, const int &seat, const int &money, const int &cards);
  void bet();
  void chatMessage(const QString &message);
  ~GameUI();
 private:
  Ui::GameUI *ui;
  QVector<Player *> players_;
  QVector<Seat *> seats_;
  QVector<QLabel *> cards_;
  Player *me_;
  QString name_;
  int bet_;
  int pot_;
 signals:
  void sendChat(const QString &message);
  void call();
  void fold();
  void bet(const int &);
  void changeSeat(const int &);

 private slots:
  void test();
  void showGUI();
  void showBetOnTable();
  void setupSeats();
  void setupCards();
  void hideBet();
  void on_buttonSitInSeat0_clicked();
  void on_buttonSitInSeat1_clicked();
  void on_buttonSitInSeat2_clicked();
  void on_buttonSitInSeat3_clicked();
  void on_buttonSitInSeat4_clicked();
  void on_buttonSitInSeat5_clicked();
  void on_buttonSitInSeat6_clicked();
  void on_buttonSitInSeat7_clicked();
  void on_buttonFold_clicked();
  void on_buttonBet_clicked();
  void on_horizontalBetSlider_sliderMoved(int position);
  void on_buttonIncrementBet_clicked();
  void on_horizontalBetSlider_valueChanged(int value);
  void on_buttonDecrementBet_clicked();
  void on_buttonCancel_clicked();
  void on_buttonSubmit_clicked();
  void on_buttonCall_clicked();
  void on_messageBox_editingFinished();

  void startGame();
};

#endif // GAMEUI_H
