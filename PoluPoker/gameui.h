#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include "player.h"
#include "seat.h"
namespace Ui {
class GameUI;
}

class GameUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameUI(const QString &tableName, const QString &myName, QWidget *parent = nullptr);
    ~GameUI();
private:
    Ui::GameUI *ui;
    QVector<Player*> players_;
    QVector<Seat*> seats_;
    QVector<QLabel *> cards_;
    Player *me_;
    QString name_;
    int currentBet_;
private slots:
    void test();
    void showGUI();
    void showBetOnTable(const int &bet);
    void setupSeats();
    void setupCards();
    void bet();
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
};

#endif // GAMEUI_H
