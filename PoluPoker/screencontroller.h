#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QtWidgets>
#include <QTcpSocket>
#include <QtMultimedia/QMediaPlayer>
#include <QThread>

#include "mainwindow.h"
#include "authentication.h"
#include "serverconnecter.h"
#include "gameui.h"

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
    ServerConnecter *servConnect_;
    QThread *thread;
    GameUI *ui_;

    void parseLogin(const QVector<QString> &commands);
    void parseRegist(const QVector<QString> &commands);
    void createMenu();
    void testTable();
private slots:
    void readingData();
    void sendToServer(const QString &command);
    void connectToServer(const QString& servAddress);
};

#endif // SCREENCONTROLLER_H
