#include "senderreciver.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>

SenderReceiver::SenderReceiver(QTcpSocket *socket, QObject *parent)
	:
	QObject{parent}, socket_(socket) {
  connect(socket_, SIGNAL(readyRead()), this, SLOT(readData()));
  qDebug() << "CREATE SENDER/RECIVER";
}

SenderReceiver::~SenderReceiver() {
  qDebug() << "DELETE SENDER/RECIVER";
  if (socket_) {
	socket_->close();
  }
  delete socket_;
}

void SenderReceiver::send(const QString &str) {
  if (socket_->isOpen()) {
	socket_->write(toJSON(str));
  }
}

QByteArray SenderReceiver::toJSON(const QString &string) {
  auto stringVec = string.split(SEPARATOR).toVector();
  QJsonObject obj;
  auto command = stringVec[0];
  std::cout << command.toStdString() << std::endl;
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
	assert(stringVec.size() == 3);
	obj.insert("command", command);
	obj.insert("table_name", stringVec[1]);
	obj.insert("player_name", stringVec[2]);
  } else if (command == "CHANGE_SEAT") {
	assert(stringVec.size() == 4);
	obj.insert("command", command);
	obj.insert("table_name", stringVec[1]);
	obj.insert("player_name", stringVec[2]);
	obj.insert("new_seat", stringVec[3]);
  } else if (command == "UPDATE_TABLES"){
	assert(stringVec.size() == 1);
	obj.insert("command", command);
  } else if (command == "CHAT"){
	assert(stringVec.size() == 4);
	obj.insert("command", command);
	obj.insert("table", stringVec[1]);
	obj.insert("player", stringVec[2]);
	obj.insert("message", stringVec[3]);
  } else if (command == "FOLD"){
	assert(stringVec.size() == 3);
	obj.insert("command", command);
	obj.insert("table", stringVec[1]);
	obj.insert("player", stringVec[2]);
  } else if (command == "CALL"){
	assert(stringVec.size() == 3);
	obj.insert("command", command);
	obj.insert("table", stringVec[1]);
	obj.insert("player", stringVec[2]);
  } else if (command == "BET"){
	assert(stringVec.size() == 4);
	obj.insert("command", command);
	obj.insert("table", stringVec[1]);
	obj.insert("player", stringVec[2]);
	obj.insert("bet", stringVec[3].toInt());
  } else if (command == "CHANGE_SEAT"){
	assert(stringVec.size() == 4);
	obj.insert("command", command);
	obj.insert("table", stringVec[1]);
	obj.insert("player", stringVec[2]);
	obj.insert("seat", stringVec[3].toInt());
  }
  QJsonDocument doc(obj);
  QByteArray arr = doc.toJson(QJsonDocument::Indented);
  std::cout << arr.toStdString() << std::endl;
  return arr;
}

void SenderReceiver::readData() {
  QByteArray data = socket_->readAll();
  QJsonParseError jsonError{};
  auto json = QJsonDocument::fromJson(data, &jsonError);
  if (jsonError.error != QJsonParseError::NoError) {
	std::cout << "JSON Error: " << jsonError.errorString().toStdString() << std::endl;
  }
  std::cout << QString(json.toJson(QJsonDocument::Indented)).toStdString() << std::endl;
  parse(json);
}

void SenderReceiver::parse(const QJsonDocument &jsonDoc) {
  QJsonObject obj = jsonDoc.object();
  QString command = obj["command"].toString();
  if (command == "REGIST" or command == "LOGIN") {
	QString result = obj["result"].toString();
	if (result == "SUCCESS") {
	  QJsonArray tables = obj["tables"].toArray();
	  QStringList tableNames;
	  for (auto it = tables.begin(); it != tables.end(); ++it) {
		tableNames.push_back(it->toObject()["name"].toString());
	  }
	  emit loginRegistSuccess(tableNames);
	  return;
	}
	if (result.contains("UNIQUE constraint failed")) result = "User already exists";
	emit loginRegistFail(result);
	return;
  } else if (command == "CREATE") {
	QString result = obj["result"].toString();
	if (result == "SUCCESS") {
	  QString name = obj["name"].toString();
	  emit createSuccess(name);
	  return;
	}
	emit createError(result);
	return;
  } else if (command == "CONNECT") {
//	std::cout << "PARSE" << std::endl;
	QString result = obj["result"].toString();
	if (result != "SUCCESS") {
	  emit connectError(result);
	  return;
	}
	std::cout << obj["table_name"].toString().toStdString() << std::endl;
	emit connectSuccess(obj["table_name"].toString(), obj["bet"].toInt(), obj["pot"].toInt());
	QJsonArray arr = obj["players"].toArray();
	for (const auto &it : arr) {
	  auto player = it.toObject();
	  emit addPlayerToTable(player["name"].toString(),
							player["seat"].toInt(),
							player["money"].toInt(),
							player["cards"].toInt());
	}
  } else if (command == "UPDATE_TABLES"){
	QString result = obj["result"].toString();
	if (result != "SUCCESS"){
	  return;
	}
	QJsonArray arr = obj["tables"].toArray();
	QStringList list;
	for (const auto &it: arr){
	  list.append(it.toObject()["name"].toString());
	}
	std::cout << "UPDATED TABLES" << std::endl;
	for (const auto &it: list){
	  std::cout << it.toStdString() << std::endl;
	}
	emit updateTables(list);
  }
}

