#include "senderreciver.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>

SenderReciver::SenderReciver(QTcpSocket *socket, QObject *parent) :
	QObject{parent}, socket_(socket) {
  connect(socket_, SIGNAL(readyRead()), this, SLOT(readData()));
  qDebug() << "CREATE SENDER/RECIVER";
}

SenderReciver::~SenderReciver() {
  qDebug() << "DELETE SENDER/RECIVER";
  if (socket_) {
	socket_->close();
  }
  delete socket_;
}

void SenderReciver::send(const QString &str) {
  if (socket_->isOpen()) {
	socket_->write(toJSON(str));
  }
}

QByteArray SenderReciver::toJSON(const QString &string) {
  auto stringVec = string.split(" ").toVector();
  QJsonObject obj;
  auto command = stringVec[0];
  if (command == "REGIST" or command == "LOGIN") {
	assert(stringVec.size() == 3);
	obj.insert("command", command);
	obj.insert("login", stringVec[1]);
	obj.insert("password", stringVec[2]);
  } else if (command == "CREATE") {
	assert(stringVec.size() == 3);
	obj.insert("command", command);
	obj.insert("name", stringVec[1]);
	obj.insert("size", stringVec[2].toInt());
  } else if (command == "CONNECT") {
	assert(stringVec.size() == 4);
	obj.insert("command", command);
	obj.insert("table_name", stringVec[1]);
	obj.insert("player_name", stringVec[2]);
	obj.insert("coins", stringVec[3].toInt());
  } else if (command == "CHANGE_SEAT") {
	assert(stringVec.size() == 3);
	obj.insert("command", command);
	obj.insert("player_name", stringVec[1]);
	obj.insert("new_seat", stringVec[2]);
  }
  QJsonDocument doc(obj);
  QByteArray arr = doc.toJson(QJsonDocument::Indented);
  std::cout << arr.toStdString() << std::endl;
  return arr;
}

void SenderReciver::readData() {
  QByteArray data = socket_->readAll();
  QJsonParseError jsonError{};
  auto json = QJsonDocument::fromJson(data, &jsonError);
  if (jsonError.error != QJsonParseError::NoError) {
	std::cout << "JSON Error: " << jsonError.errorString().toStdString() << std::endl;
  }
  std::cout << QString(json.toJson(QJsonDocument::Indented)).toStdString() << std::endl;
  parse(json);
}

void SenderReciver::parse(const QJsonDocument &jsonDoc) {
  QJsonObject obj = jsonDoc.object();
  QString command = obj.value("command").toString();
  if (command == "REGIST" or command == "LOGIN") {
	QString result = obj.value("result").toString();
	if (result == "SUCCESS") {
	  QJsonArray tables = obj.value("tables").toArray();
	  QStringList tableNames;
	  for (auto it = tables.begin(); it != tables.end(); ++it){
		tableNames.push_back(it->toObject().value("name").toString());
	  }
	  emit loginRegistSuccess(tableNames);
	} else {
	  if (result.contains("UNIQUE constraint failed")) result = "User already exists";
	  emit loginRegistFail(result);
	}
  } else if (command == "CREATE"){
	QString result = obj.value("result").toString();
	if (result == "SUCCESS"){
	  QString name = obj.value("name").toString();
	  emit createSuccess(name);
	} else{
	  emit createError(result);
	}
  }
}

