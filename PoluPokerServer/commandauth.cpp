#include "commandauth.h"
#include <QTcpSocket>
#include <iostream>

CommandAuth::CommandAuth(QSqlDatabase *base, QString &login, QString &password, const bool &isLogin)
	: base_(base), login_(login), password_(password), isLogin_(isLogin) {

}

QJsonDocument CommandAuth::login() {
  QSqlQuery qry;
  QJsonObject obj;
  QJsonDocument doc;
  obj.insert("command", "LOGIN");
  bool ok = qry.prepare("SELECT * FROM Users WHERE username = :username AND password = :password");
  if (!ok) {
	obj.insert("result", qry.lastError().text());
	doc.setObject(obj);
	return doc;
  }
  qry.bindValue(":username", login_);
  qry.bindValue(":password", password_);
  if (!qry.exec()) {
	obj.insert("result", qry.lastError().text());
	return doc;
  }
  if (qry.next()) {
	obj.insert("result", "SUCCESS");
  } else {
	std::cout << qry.lastError().text().toStdString() << std::endl;
	obj.insert("result", "FAIL");
  }
  doc.setObject(obj);
  return doc;
}
QJsonDocument CommandAuth::exec() {
  return (isLogin_) ? login() : regist();
}
QJsonDocument CommandAuth::regist() {
  QJsonObject obj;
  QJsonDocument doc;
  obj.insert("command", "REGIST");
  QSqlQuery qry;
  bool ok = qry.prepare("INSERT INTO Users (username, password) "
						"VALUES (:username, :password)");
  if (!ok) {
	obj.insert("result", qry.lastError().text());
	doc.setObject(obj);
	return doc;
  }
  qry.bindValue(":username", login_);
  qry.bindValue(":password", password_);
  if (qry.exec()) {
	obj.insert("result", "SUCCESS");
	doc.setObject(obj);
  } else {
	obj.insert("result", qry.lastError().text());
	doc.setObject(obj);
  }
  return doc;
}

