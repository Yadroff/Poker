#include "screencontroller.h"
#include <QSound>
#include <qtestsupport_core.h>



ScreenController::ScreenController(QObject *parent)
	:
	QObject(parent) {
//    testTable();
//    this->menu_ = new MainWindow();
//    this->menu_->show();
  loader_ = new Loader();
  loader_->show();
  loader_->setStatus("Connecting to the server");
  QTest::qWait(1000);
  thread = new QThread(this);
  servConnect_ = new ServerConnecter();
  servConnect_->moveToThread(thread);
  connect(thread, SIGNAL(started()), servConnect_, SLOT(run()));
  connect(servConnect_, SIGNAL(finished(QString)), this, SLOT(connectToServer(QString)));
  thread->start();
}

ScreenController::~ScreenController() {
  if (servConnect_) {
	servConnect_->setRun(false);
  }
  if (thread) {
	thread->quit();
	thread->wait();
  }
  delete thread;
  delete servConnect_;
  delete loader_;
}

void ScreenController::setLogin(const QString &newLogin) {
  login_ = newLogin;
}

void ScreenController::loginFail(const QString &error) {
  this->loader_->hide();
  this->auth_->show();
  QMessageBox::critical(this->auth_, "FAIL", error);
  this->auth_->setEnabled(true);
}

void ScreenController::createMenu(const QStringList &tables) {
  QTest::qWait(1000);
  this->menu_ = new MainWindow(tables);
  this->auth_->close();
  this->loader_->close();
  this->menu_->show();
//    connect(menu_, SIGNAL(needToSend(const QString &)), this->senderReceiver_, SLOT(send(const QString &)));
  connect(menu_, SIGNAL(signalCreateTable(QString)), this, SLOT(createTableRequest(QString)));
  connect(menu_, SIGNAL(signalConnectTable(QString)), this, SLOT(connectTableRequest(QString)));
  connect(menu_, SIGNAL(signalUpdateTables()), this, SLOT(updateTableRequest()));
  connect(senderReceiver_, SIGNAL(updateTables(QStringList)), menu_, SLOT(updateTablesList(QStringList)));
}

void ScreenController::createTableRequest(const QString &name) {
  this->menu_->hide();
  this->loader_->show();
  this->loader_->setStatus("Sending create request");
  QTest::qWait(1000);
  QString string = "CREATE" + SEPARATOR + name + SEPARATOR + QString::number(TABLE_SIZE);
  std::cout << string.toStdString() << std::endl;
  senderReceiver_->send(string);
  this->loader_->setStatus("Wait server");
}

void ScreenController::connectTableRequest(const QString &name) {
  std::cout << "CONNECT TABLE REQUEST" << std::endl;
  this->menu_->hide();
  this->loader_->show();
  this->loader_->setStatus("Sending connect request");
  QTest::qWait(1000);
  QString command = "CONNECT" + SEPARATOR + name + SEPARATOR + login_;
  std::cout << command.toStdString() << std::endl;
  senderReceiver_->send(command);
  this->loader_->setStatus("Wait server");
}

void ScreenController::testTable() {
//    table_ = new Table();
//    table_->putCardOnTable("Spades", "Ace");
//    table_->putCardOnTable("Diamonds", "Ace");
//    table_->putCardOnTable("Diamonds", "Two");
//    table_->putCardOnTable("Hearts", "Eight");
//    table_->putCardOnTable("Clubs", "Jack");
//    table_->show();
  table_ = new GameUI("My table", "Yadroff", 0, 0);
  table_->show();
}

void ScreenController::connectToServer(const QString &string) {
//    this->auth_->stopLoad();
  std::cout << string.toStdString() << std::endl;
  servConnect_->setRun(false);
  thread->quit();
  thread->wait();
  delete thread;
  delete servConnect_;
  thread = nullptr;
  servConnect_ = nullptr;
  auto stringList = string.split(":");
  if (stringList.size() < 2) {
	std::cout << "Can not connect to server" << std::endl;
	QMessageBox::critical(this->loader_, "CONNECTION FAIL", string);
	return;
  }
  auto socket_ = new QTcpSocket();
  socket_->connectToHost(stringList.last(), SERVER_PORT);
  if (!socket_->waitForConnected()) {
	std::cout << "Can not to connect: " << socket_->errorString().toStdString() << std::endl;
	QMessageBox::critical(this->loader_, "CONNECTION FAIL", socket_->errorString());
	return;
  }
  loader_->hide();
  this->auth_ = new Authentication();
  this->auth_->show();
  connect(this->auth_, SIGNAL(changeLogin(QString)), this, SLOT(setLogin(QString)));
  std::cout << "CONNECTED TO SERVER: IP: " << stringList.last().toStdString() << std::endl;
  createSenderReceiver(socket_);
}

void ScreenController::createFail(const QString &error) {
  this->loader_->hide();
  this->menu_->show();
  QMessageBox::critical(this->menu_, "CREATE FAIL", error);
}
void ScreenController::createTable(const QString &name) {
  connectTableRequest(name);
}
void ScreenController::connectTable(const QString &name, const int &pot, const int &bet) {
  if (table_) {
	delete table_;
  }
  std::cout << "CREATE TABLE NAME: " << name.toStdString() << std::endl;
  table_ = new GameUI(name, login_, bet, pot);
  connect(table_, SIGNAL(send(QString)), senderReceiver_, SLOT(send(QString)));
//  connect(table_, SIGNAL(changeSeat(const int &)), this, SLOT());
  loader_->hide();
  table_->show();
}
void ScreenController::login(const QString &command) {
  this->auth_->hide();
  this->loader_->show();
  this->loader_->setStatus("Send request to server");
  QTest::qWait(1000);
  senderReceiver_->send(command);
  this->loader_->setStatus("Wait for server");
}
void ScreenController::createSenderReceiver(QTcpSocket *socket) {
  senderReceiver_ = new SenderReceiver(socket, this);
  connect(auth_, SIGNAL(needToSend(QString)), this, SLOT(login(QString)));
  connect(senderReceiver_, SIGNAL(loginRegistSuccess(QStringList)), this, SLOT(createMenu(QStringList)));
  connect(senderReceiver_, SIGNAL(loginRegistFail(QString)), this, SLOT(loginFail(QString)));
  connect(senderReceiver_, SIGNAL(createSuccess(QString)), this, SLOT(createTable(QString)));
  connect(senderReceiver_, SIGNAL(createError(QString)), this, SLOT(createFail(QString)));
  connect(senderReceiver_, SIGNAL(connectSuccess(QString, int, int)), this, SLOT(connectTable(QString, int, int)));
}
void ScreenController::updateTableRequest() {
  senderReceiver_->send("UPDATE_TABLES");
}

