#include "authentication.h"
#include "ui_authentication.h"

#include <iostream>

Authentication::Authentication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Authentication)
{
    ui->setupUi(this);
    ui->lineLogin->setPlaceholderText("Write your LOGIN");
    ui->linePassword->setPlaceholderText("Write your PASSWORD");
    this->setWindowState(Qt::WindowMaximized);
}

Authentication::~Authentication()
{
    delete ui;
}

void Authentication::on_buttonRegister_clicked()
{
    QString password = ui->linePassword->text();
    QString login = ui->lineLogin->text();
    bool ok = isValidString(password) and isValidString(login);
    if (!ok){
        QMessageBox::information(this, "Incorrect password", "Use only a-z, A-Z, 0-9. No spaces, no special symbols");
        ui->lineLogin->clear();
        ui->linePassword->clear();
        return;
    }
    if (password.isEmpty() or login.isEmpty()){
        QMessageBox::critical(this, "ERROR", "Login or password is empty");
        return;
    }
    transformString(password);
    QString command = "REGIST " + login + QString(" ") + password;
    password = "";
    emit needToSend(command);
}


void Authentication::on_buttonLogin_clicked()
{
    QString password = ui->linePassword->text();
    QString login = ui->lineLogin->text();
    bool ok = isValidString(password) and isValidString(login);
    if (!ok){
        QMessageBox::information(this, "Incorrect password", "Use only a-z, A-Z, 0-9. No spaces, no special symbols");
        ui->lineLogin->clear();
        ui->linePassword->clear();
        return;
    }
    if (password.isEmpty() or login.isEmpty()){
        QMessageBox::critical(this, "ERROR", "Login or password is empty");
        return;
    }
    transformString(password);
    QString command = "LOGIN " + login + QString(" ") + password;
    password = "";
    emit needToSend(command);
}

bool Authentication::isValidString(QString &string)
{
    for (auto &c: string){
        if (c.isDigit() or c.isLetter()){
            continue;
        }
        return false;
    }
    return true;
}

void Authentication::transformString(QString &string)
{
    for (int i = 0; i < string.size(); ++i){
        string[i] = QChar(string[i].unicode() ^ KEY_VERNAM[i % KEY_SIZE].unicode());
    }
}

