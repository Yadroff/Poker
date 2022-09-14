#ifndef COMMANDLOGIN_H
#define COMMANDLOGIN_H

#include <QtSql>
#include <QSqlDatabase>
#include <QJsonDocument>
#include <QJsonObject>

#include "command.h"

class CommandAuth : public Command {
 public:
  explicit CommandAuth(QSqlDatabase *base, QString &login, QString &password, const bool &isLogin);

  QJsonDocument exec();

  QJsonDocument login();

  QJsonDocument regist();

  ~CommandAuth() = default;
 private:
  QSqlDatabase *base_;
  QString login_;
  QString password_;
  bool isLogin_;
 signals:

};

#endif // COMMANDLOGIN_H
