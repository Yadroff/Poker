#include "authentication.h"
#include "ui_authentication.h"

#include <iostream>
#include <QDesktopWidget>

Authentication::Authentication(QWidget *parent)
	:
	QMainWindow(parent),
	ui(new Ui::Authentication) {
  ui->setupUi(this);
  ui->lineLogin->setPlaceholderText("Write your LOGIN");
  ui->linePassword->setPlaceholderText("Write your PASSWORD");
  this->setWindowState(Qt::WindowFullScreen);
//    load_ = new Load(this);
//    QDesktopWidget deskWid;
//    auto rect = deskWid.screenGeometry(ui->centralwidget);
//    int x = rect.width() - load_->geometry().width();
//    int y = rect.height() - load_->geometry().height();
//    load_->setGeometry(x / 2, y / 2, load_->geometry().width(), load_->geometry().height());
}

Authentication::~Authentication() {
  delete ui;
  //    delete load_;
}

void Authentication::setEnabled(const bool &status) {
  ui->buttonLogin->setEnabled(status);
  ui->buttonRegister->setEnabled(status);
}

//void Authentication::load()
//{
//    load_->show();
//}

//void Authentication::stopLoad()
//{
//    load_->hide();
//    load_->deleteLater();
//}

void Authentication::on_buttonRegister_clicked() {
  QString password = ui->linePassword->text();
  QString login = ui->lineLogin->text();
  bool ok = isValidString(password) and isValidString(login);
  if (!ok) {
	QMessageBox::information(this, "Incorrect password", "Use only a-z, A-Z, 0-9. No spaces, no special symbols");
	ui->lineLogin->clear();
	ui->linePassword->clear();
	return;
  }
  if (password.isEmpty() or login.isEmpty()) {
	QMessageBox::critical(this, "ERROR", "Login or password is empty");
	return;
  }
  transformString(password);
  QString command = "REGIST " + login + QString(" ") + password;
  password = "";
  setEnabled(false);
  emit needToSend(command);
  emit changeLogin(login);
}

void Authentication::on_buttonLogin_clicked() {
  QString password = ui->linePassword->text();
  QString login = ui->lineLogin->text();
  bool ok = isValidString(password) and isValidString(login);
  if (!ok) {
	QMessageBox::information(this, "Incorrect password", "Use only a-z, A-Z, 0-9. No spaces, no special symbols");
	ui->lineLogin->clear();
	ui->linePassword->clear();
	return;
  }
  if (password.isEmpty() or login.isEmpty()) {
	QMessageBox::critical(this, "ERROR", "Login or password is empty");
	return;
  }
  transformString(password);
  QString command = "LOGIN " + login + QString(" ") + password;
  password = "";
  setEnabled(false);
  emit needToSend(command);
  emit changeLogin(login);
}

bool Authentication::isValidString(QString &string) {
  for (auto &c : string) {
	if (c.isDigit() or c.isLetter()) {
	  continue;
	}
	return false;
  }
  return true;
}

void Authentication::transformString(QString &string) {
  for (int i = 0; i < string.size(); ++i) {
	string[i] = QChar(string[i].unicode() ^ KEY_VERNAM[i % KEY_SIZE].unicode());
  }
}

