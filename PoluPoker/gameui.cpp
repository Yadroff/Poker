#include "gameui.h"
#include "ui_gameui.h"
#include <QVBoxLayout>

GameUI::GameUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameUI)
{
    ui->setupUi(this);
    auto palette = ui->buttonCancel->palette();
    palette.setColor(QPalette::Button, QColor(88, 32, 32));
    ui->buttonCancel->setPalette(palette);
    this->setWindowState(Qt::WindowMaximized);
}

GameUI::~GameUI()
{
    delete ui;
}
