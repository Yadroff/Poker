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
    explicit GameUI(QWidget *parent = nullptr);
    ~GameUI();
    void setupSeats();
private:
    Ui::GameUI *ui;
    QVector<Player*> players_;
    QVector<Seat*> seats_;
//    Player *me_;
};

#endif // GAMEUI_H
