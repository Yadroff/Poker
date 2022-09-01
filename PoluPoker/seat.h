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

    void addPlayer(const QString &playerName, const int &money, const int &cardsCount_);

    bool isAvailable() const;

    void free();

    void setCardPixmap(const int &number, const QPixmap &pixmap);

    void changeMoney(const int &newMoney);

    void hideAll();
private:
    QVector<QLabel*> *coins_;
    QVector<QLabel*> *cards_;
    int cardsCount_;
    QLabel *place_, *name_, *money_;
    QPushButton *button_;
    bool isAvailable_;
private slots:
signals:

};

#endif // SEAT_H
