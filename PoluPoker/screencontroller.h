#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QTcpSocket>
#include <QThread>

#include "menu/mainwindow.h"
#include "authentication/authentication.h"
#include "serverChatting/serverconnecter.h"
#include "serverChatting/senderreciver.h"
#include "gameUI/gameui.h"

const quint16 SERVER_PORT = 7777;
class ScreenController: public QObject
{
    Q_OBJECT
public:
    explicit ScreenController(QObject *parent = nullptr);
    ~ScreenController();

    const QString &login() const;

private:
    MainWindow *menu_;
    Authentication *auth_;
    ServerConnecter *servConnect_;
    QThread *thread;
    GameUI *table_;
    SenderReciver *senderReciver_;
    QString login_;
    void testTable();
private slots:
    void setLogin(const QString &newLogin);
    void connectToServer(const QString& servAddress);
    void loginFail(const QString &);
    void createMenu(const QStringList &tables);
    void createTable(const QString &name);
    void connectTable(const QString &name);
};

#endif // SCREENCONTROLLER_H
