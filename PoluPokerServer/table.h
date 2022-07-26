#ifndef TABLE_H
#define TABLE_H

#include <QObject>

class Table : public QObject
{
    Q_OBJECT
public:
    explicit Table(QObject *parent, const QString &string);
    QString name() const;
    QVector<int> players() const;
signals:
private:
    QString name_;
    QVector<int> players_;
};

#endif // TABLE_H
