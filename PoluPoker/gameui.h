#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include "player.h"

namespace Ui {
class gameUI;
}

class gameUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameUI(QWidget *parent = nullptr);
    ~gameUI();

private:
    Ui::gameUI *ui;
    QVector<Player*> players_;
};

#endif // GAMEUI_H
