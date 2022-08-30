#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{

}

Player::Player(const QString &name, const int &seat, QLabel *card1, QLabel *card2, QLabel *labelName, QLabel *coins):
    name_(name), seat_(seat), money_(DEFAULT_COINS) {}

void Player::leaveTable()
{

}
