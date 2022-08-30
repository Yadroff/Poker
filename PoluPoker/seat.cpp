#include "seat.h"

Seat::Seat(QVector<QLabel *> *coins, QVector<QLabel*> *cards, QLabel *place, QLabel *name, QLabel *money, QPushButton *button):
    coins_(coins), cards_(cards), place_(place), name_(name), money_(money), button_(button), isAvailable_(true){
    hide();
}

void Seat::hide()
{
    for (auto *coin: *coins_){
        coin->hide();
    }
    for (auto *card: *cards_){
        card->hide();
    }
    name_->hide();
    place_->hide();
    money_->hide();
    button_->show();
}

void Seat::show()
{
    for (auto *coin: *coins_){
        coin->show();
    }
    for (auto *card: *cards_){
        card->show();
    }
    name_->show();
    place_->show();
    money_->show();
    button_->hide();
}

void Seat::addPlayer(const QString &playerName, const int &money)
{
    name_->setText(playerName);
    money_->setText(QString::number(money));
    isAvailable_ = false;
    show();
}
