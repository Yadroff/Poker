#include "gameui.h"
#include "ui_gameui.h"

gameUI::gameUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameUI)
{
    ui->setupUi(this);
}

gameUI::~gameUI()
{
    delete ui;
}
