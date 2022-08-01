#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QtWidgets>
#include <QTcpSocket>
#include <QtMultimedia/QMediaPlayer>

#include "mainwindow.h"
#include "authentication.h"
#include "table.h"


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

    void getHost(QString &ip, quint16 &port);
    void parseLogin(const QVector<QString> &commands);
    void parseRegist(const QVector<QString> &commands);
    void createMenu();
private slots:
    void readingData();
    void sendToServer(const QString &command);
};

#endif // SCREENCONTROLLER_H
