#ifndef TABLE_H
#define TABLE_H

#include <QWidget>

class Table : public QWidget
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = nullptr);

signals:
    void needToSend(const QString &command);
};

#endif // TABLE_H
