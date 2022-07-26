#include "authentication.h"
#include "ui_authentication.h"

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

}


void Authentication::on_buttonLogin_clicked()
{

}

