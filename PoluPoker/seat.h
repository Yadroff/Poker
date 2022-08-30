#ifndef SEAT_H
#define SEAT_H

#include <QObject>
#include <QLabel>
class Seat : public QObject
{
    Q_OBJECT
public:
    explicit Seat(QObject *parent = nullptr);

    void hide();

private:
    QLabel *
    bool isAvailable_;
signals:

};

#endif // SEAT_H
