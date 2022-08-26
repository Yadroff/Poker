#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QtWidgets>
#include <QTcpSocket>
#include <QUdpSocket>
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
    QTcpSocket *socket_;
    QUdpSocket *udpSocket_;
    MainWindow *menu_;
    Table *table_;
    Authentication *auth_;
    QString serverAddress_;
    quint16 serverPort_;
    bool hasServerAddress_;

    void getHost(QString &ip, quint16 &port);
    void parseLogin(const QVector<QString> &commands);
    void parseRegist(const QVector<QString> &commands);
    void createMenu();
private slots:
    void readingData();
    void sendToServer(const QString &command);
    void connectToServer();
};

#endif // SCREENCONTROLLER_H
