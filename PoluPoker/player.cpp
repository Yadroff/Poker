#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{

}

Player::Player(const QString &name, const int &seat): name_(name), seat_(seat), money_(DEFAULT_COINS){}
