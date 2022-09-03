#include "load.h"
#include "ui_load.h"

Load::Load(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Load)
{
    ui->setupUi(this);
    movie_ = new QMovie(":/images/load.gif");
    ui->gif->setMovie(movie_);
    movie_->start();
}

Load::~Load()
{
    delete ui;
}
