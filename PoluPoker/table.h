#ifndef TABLE_H
#define TABLE_H

#include <QtWidgets>
#include "card.h"

namespace Ui {
class Table;
}

class Table : public QWidget
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = nullptr);
    ~Table();
    void putCardOnTable(const QString &suit, const QString &nominal);

private:
    Ui::Table *ui;
    QVector<QLabel *> labelsCards_;
    int cards_;
    Card card_;
};

#endif // TABLE_H
