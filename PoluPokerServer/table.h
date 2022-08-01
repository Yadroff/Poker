#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include "player.h"

class Table : public QObject
{
    Q_OBJECT
public:
    explicit Table(const QString &name, QObject *parente = nullptr);
    QString name() const;
    QVector<Player> players() const;
signals:
private:
    QString name_;
    QVector<Player> players_;
};

#endif // TABLE_H
