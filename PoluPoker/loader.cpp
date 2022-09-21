#include "loader.h"
#include "ui_loader.h"

Loader::Loader(QWidget *parent)
	:
	QMainWindow(parent),
	ui(new Ui::Loader) {
  ui->setupUi(this);
  QPalette palette;
  QPixmap pixmap(":/images/backgroundLoad.jpg");
  palette.setBrush(QPalette::Window, pixmap);
  this->setPalette(palette);
  movie_ = new QMovie(":/images/load.gif");
  ui->labelGIF->setMovie(movie_);
  movie_->start();
}

Loader::~Loader() {
  delete ui;
}

void Loader::setStatus(const QString &status) {
  ui->labelStatus->setText(status);
}
