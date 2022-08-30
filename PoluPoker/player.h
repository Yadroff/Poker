#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <seat.h>

const int DEFAULT_COINS = 5000;
class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    Player(const QString &name, const int &seat, QLabel *card1, QLabel *card2, QLabel *labelName, QLabel *coins);
private:
    QString name_;
    qint32 seat_;
    qint32 money_;
    Seat *seat;
public slots:
    void leaveTable();
};

#endif // PLAYER_H
