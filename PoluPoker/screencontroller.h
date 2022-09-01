#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QtWidgets>
#include <QTcpSocket>
#include <QtMultimedia/QMediaPlayer>
#include <QThread>

#include "mainwindow.h"
#include "authentication.h"
#include "serverconnecter.h"
#include "senderreciver.h"
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
    Authentication *auth_;
    ServerConnecter *servConnect_;
    QThread *thread;
    GameUI *ui_;
    SenderReciver *senderReciver_;

    void testTable();
private slots:
    void sendToServer(const QString &command);
    void connectToServer(const QString& servAddress);
    void loginFail(const QString &);
    void createMenu();
};

#endif // SCREENCONTROLLER_H
