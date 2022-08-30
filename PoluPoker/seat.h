#ifndef SEAT_H
#define SEAT_H

#include <QObject>
#include <QLabel>
#include <QPushButton>

class Seat : public QObject
{
    Q_OBJECT
public:
    explicit Seat(QVector<QLabel*> *coins, QVector<QLabel*> *cards, QLabel *place, QLabel *name, QLabel *money, QPushButton *button);

    void hide();

    void show();

private:
    QVector<QLabel*> *coins_;
    QVector<QLabel*> *cards_;
    QLabel *place_, *name_, *money_;
    QPushButton *button_;
    bool isAvailable_;
private slots:
    void addPlayer(const QString &playerName, const int &money);
signals:

};

#endif // SEAT_H
