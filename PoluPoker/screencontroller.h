#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QTcpSocket>
#include <QThread>
#include "menu/mainwindow.h"
#include "authentication/authentication.h"
#include "serverChatting/serverconnecter.h"
#include "serverChatting/senderreciver.h"
#include "gameUI/gameui.h"
#include "loader.h"

const quint16 SERVER_PORT = 7777;
const int TABLE_SIZE = 8;

class ScreenController : public QObject {
 Q_OBJECT
 public:
  explicit ScreenController(QObject *parent = nullptr);
  ~ScreenController();

 private:
  MainWindow *menu_{};
  Authentication *auth_;
  ServerConnecter *servConnect_;
  QThread *thread;
  GameUI *table_{};
  SenderReceiver *senderReceiver_{};
  Loader *loader_;
  QString login_;
  const QString SEPARATOR = QString(QChar(7));

  void testTable();
 private slots:
  void setLogin(const QString &newLogin);
  void connectToServer(const QString &servAddress);
  void loginFail(const QString &);
  void createMenu(const QStringList &tables);
  void createTableRequest(const QString &name);
  void createTable(const QString &name);
  void connectTableRequest(const QString &name);
  void connectTable(const QString &name, const int &pot, const int &bet);
  void createFail(const QString &error);
  void login(const QString &command);
  void createSenderReceiver(QTcpSocket *socket);
  void updateTableRequest();
};

#endif // SCREENCONTROLLER_H
