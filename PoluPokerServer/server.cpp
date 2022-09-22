#include "server.h"
#include <QThread>
#include <iostream>

Server::Server(QWidget *parent) : QWidget(parent) {
  senderBroadcast_ = new Sender();
  threadBroadcast_ = new QThread(this);
  senderBroadcast_->moveToThread(threadBroadcast_);
  connect(threadBroadcast_, SIGNAL(started()), senderBroadcast_, SLOT(run()));
  connect(senderBroadcast_, SIGNAL(finished()), senderBroadcast_,
		  SLOT(deleteLater()));
  connect(senderBroadcast_, SIGNAL(finished()), threadBroadcast_, SLOT(quit()));
  connect(threadBroadcast_, SIGNAL(finished()), threadBroadcast_,
		  SLOT(deleteLater()));
  threadBroadcast_->start();
  buttonShutDown_ = new QPushButton(this);
  QPixmap pixmap(":/image/Shutdown_button.jpg");
  QIcon buttonIcon(pixmap);
  buttonShutDown_->setIcon(buttonIcon);
  buttonShutDown_->setIconSize(pixmap.rect().size());
  buttonShutDown_->setFixedSize(pixmap.rect().size());
  tcpServer_ = new QTcpServer(this);
  connect(tcpServer_, SIGNAL(newConnection()), this, SLOT(newUser()));
  if (!tcpServer_->listen(QHostAddress::Any, SERVER_PORT)) {
	perror("Server Listen");
  } else {
	isListen_ = true;
	std::cout << "STATE: SERVER STARTED" << std::endl;
  }
  connect(buttonShutDown_, SIGNAL(clicked()), this, SLOT(shutdownServer()));
  dataBase_ = QSqlDatabase::addDatabase("QSQLITE");
  dataBase_.setDatabaseName(DATA_BASE_PATH);
  if (dataBase_.open()) {
	std::cout << "OPERATION: OPEN DATA BASE: SUCCESS" << std::endl;
  } else {
	std::cout << "OPERATION: OPEN DATA BASE: FAIL" << std::endl;
  }
  test();
}

Server::~Server() {
  senderBroadcast_->setRunningFlag(false);
  threadBroadcast_->quit();
  threadBroadcast_->wait();
  threadBroadcast_->deleteLater();
  senderBroadcast_->deleteLater();
  if (dataBase_.isOpen()) {
	dataBase_.close();
	std::cout << "OPERATION: CLOSE DATA BASE: SUCCESS" << std::endl;
  }
  shutdownServer();
}

QJsonArray Server::tables() {
  QJsonArray tables;
	  foreach(const QString &tableName, tables_.keys()) {
	  QJsonObject table;
	  table.insert("name", tableName);
	  tables.push_back(table);
	}
  return tables;
}

void Server::shutdownServer() {
  if (!isListen_) {
	return;
  }
	  foreach (qint64 i, clients_.keys()) {
	  clients_[i]->close();
	  clients_.remove(i);
	  std::cout << "OPERATION: REMOVE: " << i << " CLIENT" << std::endl;
	}
	  foreach(auto table, tables_.values()) {
	  table->deleteLater();
	}
  tcpServer_->close();
  std::cout << "STATE: SERVER CLOSED" << std::endl;
  isListen_ = false;
  this->close();
}

void Server::readData() {
	  foreach (qint64 i, clients_.keys()) {
	  if (clients_[i]->bytesAvailable()) {
		QByteArray readBuff = clients_[i]->readAll();
		QJsonParseError parse{};
		QJsonDocument doc = QJsonDocument::fromJson(readBuff, &parse);
		std::cout << "NEW MESSAGE" << std::endl << QString(doc.toJson(QJsonDocument::Indented)).toStdString()
				  << std::endl;
		if (parse.error != QJsonParseError::NoError) {
		  std::cout << parse.errorString().toStdString() << std::endl;
		  continue;
		}
		auto obj = doc.object();
		auto command = obj.value("command").toString();
		QByteArray toSend;
		if (command == "REGIST") {
		  auto login = obj.value("login").toString();
		  auto password = obj.value("password").toString();
		  auto regist = new CommandAuth(&dataBase_, login, password, false);
		  auto ans = regist->exec();
		  if (ans["result"] == "SUCCESS") {
			// проверяем, вошел ли уже игрок
			auto ansObj = ans.object();
				foreach(const QString &playerName, players_.values()) {
				if (playerName == login) {
				  // вход уже произведен
				  ansObj["result"] = "ALREADY LOGGED IN";
				  ans.setObject(ansObj);
				  break;
				}
			  }
		  }
		  if (ans["result"] == "SUCCESS") {
			auto ansObj = ans.object();
			ansObj.insert("tables", tables());
			ans.setObject(ansObj);
			players_[clients_[i]] = login;
		  }
		  toSend = ans.toJson(QJsonDocument::Indented);
		  delete regist;
		} else if (command == "LOGIN") {
		  auto login = obj.value("login").toString();
		  auto password = obj.value("password").toString();
		  auto commandLogin = new CommandAuth(&dataBase_, login, password, true);
		  auto ans = commandLogin->exec();
		  if (ans["result"] == "SUCCESS") {
			// проверяем, вошел ли уже игрок
			auto ansObj = ans.object();
				foreach(const QString &playerName, players_.values()) {
				if (playerName == login) {
				  // вход уже произведен
				  ansObj["result"] = "ALREADY LOGGED IN";
				  ans.setObject(ansObj);
				  break;
				}
			  }
		  }
		  if (ans["result"] == "SUCCESS") {
			auto ansObj = ans.object();
			ansObj.insert("tables", tables());
			ans.setObject(ansObj);
			players_[clients_[i]] = login;
		  }
		  toSend = ans.toJson(QJsonDocument::Indented);
		  delete commandLogin;
		} else if (command == "CREATE") {
		  auto name = obj.value("name").toString();
		  auto size = obj.value("size").toInt();
		  auto create = new CommandCreate(tables_, name, size);
		  auto ans = create->exec();
		  toSend = ans.toJson(QJsonDocument::Indented);
		  delete create;
		} else if (command == "CONNECT") {
		  auto login = obj["player_name"].toString();
		  auto table = obj["table_name"].toString();
		  auto connect = new CommandConnect(tables_, table, login, clients_[i]);
		  auto ans = connect->exec();
		  toSend = ans.toJson(QJsonDocument::Indented);
		  delete connect;
		} else if (command == "UPDATE_TABLES"){
		  QJsonObject ansObj;
		  ansObj.insert("command", command);
		  ansObj.insert("result", "SUCCESS");
		  ansObj.insert("tables", tables());
		  toSend = QJsonDocument(ansObj).toJson(QJsonDocument::Indented);
		}
		clients_[i]->write(toSend);
		std::cout << "SEND" << std::endl << toSend.toStdString() << std::endl;
	  }
	}
}

void Server::disconnectUser() {
  auto *client = qobject_cast<QTcpSocket *>(sender());
  qint64 id = -1;
  if (client) {
	for (auto it = clients_.begin(); it != clients_.end(); ++it) {
	  if (it.value() == client) {
		id = it.key();
			foreach(auto table, tables_.values()) {
			table->leavePlayer(players_[it.value()]);
		  }
		clients_.erase(it);
		break;
	  }
	}
	players_.remove(client);
	std::cout << "OPERATION: DISCONNECT: " << id << std::endl;
	client->deleteLater();
  }
}

void Server::newUser() {
  if (isListen_) {
	while (tcpServer_->hasPendingConnections()) {
	  std::cout << "OPERATION: NEW CONNECTION" << std::endl;
	  auto *clientSocket = tcpServer_->nextPendingConnection();
	  qint64 id = clientSocket->socketDescriptor();
	  clients_[id] = clientSocket;
	  connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readData()));
	  connect(clientSocket, SIGNAL(disconnected()), this,
			  SLOT(disconnectUser()));
	}
  }
}

void Server::test() {
  tables_.insert("Abc", new Table("Abc"));
}

//void Server::sendToClient(QJsonDocument &doc, QTcpSocket *client, const bool &needWait) {
//  client->write(doc.toJson(QJsonDocument::Indented));
//  if (needWait) {
//	if (client->waitForReadyRead()) {
//	  qDebug() << "OPERATION: SEND TO CLIENT WAIT: SUCCESS";
//	} else {
//	  qWarning() << "OPERATION: SEND TO CLIENT WAIT: ERROR: NO ANSWER FROM CLIENT";
//	}
//  }
//}