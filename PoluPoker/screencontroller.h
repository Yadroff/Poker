#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QtWidgets>
#include <QTcpSocket>
#include <QtMultimedia/QMediaPlayer>

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
    QTcpSocket *socket_ = nullptr;
    MainWindow *menu_ = nullptr;
    Table *table_ = nullptr;
    Authentication *auth_ = nullptr;

    void parseLogin(const QVector<QString> &commands);
    void parseRegist(const QVector<QString> &commands);
private slots:
    void connectToTable(const QString &string);
    void createTable(const QString &string);
    void readingData();
    void sendToServer(const QString &command);
};

#endif // SCREENCONTROLLER_H
