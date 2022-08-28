#include "table.h"
#include "ui_table.h"

Table::Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Table),
    card_()
{
    ui->setupUi(this);
    labelsCards_.resize(5);
    labelsCards_[0] = ui->card1;
    labelsCards_[1] = ui->card2;
    labelsCards_[2] = ui->card3;
    labelsCards_[3] = ui->card4;
    labelsCards_[4] = ui->card5;
    cards_ = 0;
}

Table::~Table()
{
    delete ui;
}

void Table::putCardOnTable(const QString &suit, const QString &nominal)
{
    card_.setCard(suit, nominal);
    labelsCards_[cards_]->setPixmap(card_.getPixmap());
    ++cards_;
}
