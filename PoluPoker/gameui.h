#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include "player.h"

namespace Ui {
class GameUI;
}

class GameUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameUI(QWidget *parent = nullptr);
    ~GameUI();

private:
    Ui::GameUI *ui;
    QVector<Player*> players_;
};

#endif // GAMEUI_H
