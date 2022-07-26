#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QtWidgets>
#include <QTcpSocket>
#include <QProcess>

#include "mainwindow.h"
#include "authentication.h"
#include "table.h"

const quint16 SERVER_PORT = 7777;

class ScreenController: public QObject
{
    Q_OBJECT
public:
    explicit ScreenController(QObject *parent = nullptr);
    ~ScreenController();
private:
    QTcpSocket *socket_;
    MainWindow *menu_;
    Table *table_;
    Authentication *auth_;
private slots:
    void connectToTable(const QString &string);
    void createTable(const QString &string);
    void ReadingData();
};

#endif // SCREENCONTROLLER_H
