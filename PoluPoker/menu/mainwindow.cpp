#include "mainwindow.h"

MainWindow::MainWindow(const QStringList &tables, QWidget *parent)
	: QWidget(parent), tables_(tables) {
  setupUI();
//  boxTables_->addItems(tables);
  connect(exit_, &QPushButton::clicked, this, &MainWindow::exitMenu);
  connect(buttonHelp_, &QPushButton::clicked, this, &MainWindow::help);
  connect(buttonCreateTable_, &QPushButton::clicked, this, &MainWindow::createTable);
  connect(buttonConnectTable_, &QPushButton::clicked, this, &MainWindow::connectTable);
  connect(buttonCreate_, &QPushButton::clicked, this, &MainWindow::createClicked);
  connect(buttonCancelCreate_, &QPushButton::clicked, this, &MainWindow::cancelCreate);
  connect(buttonConnect_, &QPushButton::clicked, this, &MainWindow::connectClicked);
  connect(buttonCancelConnect_, &QPushButton::clicked, this, &MainWindow::cancelConnect);
}

void MainWindow::setupUI() {
  mediaPlayer_ = new QMediaPlayer;
  mediaPlayer_->setMedia(QUrl("qrc:/sounds/intro.mp3"));
  mediaPlayer_->setVolume(10);
  mediaPlayer_->play();
  QPalette palette;
  palette.setBrush(this->backgroundRole(), QBrush(QPixmap(":/images/background.jpg")));
  this->setPalette(palette);
  this->setAutoFillBackground(true);
  this->setWindowState(Qt::WindowMaximized);
  auto *layout = new QVBoxLayout();
  layout->setAlignment(Qt::AlignCenter);
  layout->setSpacing(20);

  //create Table
  buttonCreateTable_ = new Button("Create table button", "Create Table");
  layout->addWidget(buttonCreateTable_);
  buttonCreate_ = new Button("Create button", "Create");
  buttonCancelCreate_ = new Button("Cancel create button", "Cancel");
  lineCreateTable_ = new QLineEdit();
  lineCreateTable_->setMaximumWidth(200);
  lineCreateTable_->setPlaceholderText("Write table name");
  auto *createLayout = new QHBoxLayout();
  createLayout->addWidget(lineCreateTable_);
  createLayout->addWidget(buttonCreate_);
  layout->addLayout(createLayout);
  layout->addWidget(buttonCancelCreate_);
  buttonCreate_->hide();
  lineCreateTable_->hide();
  buttonCancelCreate_->hide();

  // Connect Table
  buttonConnectTable_ = new Button("Connect table button", "Connect Table");
  buttonConnect_ = new Button("Connect button table", "Connect");
  boxTables_ = new QComboBox;
  buttonCancelConnect_ = new Button("Cancel connect button", "Cancel");
  layout->addWidget(buttonConnectTable_);
  auto *connectLayout = new QHBoxLayout();
  connectLayout->addWidget(boxTables_);
  connectLayout->addWidget(buttonConnect_);
  layout->addLayout(connectLayout);
  layout->addWidget(buttonCancelConnect_);
  buttonConnect_->hide();
  buttonCancelConnect_->hide();
  boxTables_->hide();
  //others
  buttonHelp_ = new Button("Help button", "Help");
  exit_ = new Button("Exit button", "Exit");
  layout->addWidget(buttonHelp_);
  layout->addWidget(exit_);
  this->setLayout(layout);
}

MainWindow::~MainWindow() {
  delete buttonCreateTable_;
  delete buttonCreate_;
  delete buttonCancelCreate_;
  delete lineCreateTable_;

  delete buttonConnectTable_;
  delete buttonConnect_;
  delete buttonCancelConnect_;
  delete boxTables_;

  delete buttonHelp_;
  delete exit_;
  std::cout << "Main Window deleted" << std::endl;
}

void MainWindow::cancelConnect() {
  boxTables_->hide();
  buttonConnect_->hide();
  buttonCancelConnect_->hide();
  buttonConnectTable_->show();
  boxTables_->clear();
}

void MainWindow::exitMenu() {
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Quit", "Are you sure you want to quit?",
								QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
	QApplication::quit();
  }
}

void MainWindow::help() {
  QMessageBox::information(this, tr("Help"), tr("Press Alt + F4 for win"));

}

void MainWindow::createTable() {
  buttonCreate_->show();
  lineCreateTable_->show();
  buttonCancelCreate_->show();
  buttonCreateTable_->hide();
}

void MainWindow::createClicked() {
  // case line is empty
  if (lineCreateTable_->text().isEmpty()) {
	auto reply = QMessageBox::warning(this, "Create Error", "You didn't write table name");
	if (reply == QMessageBox::Yes) {
	  QApplication::quit();
	}
	return;
  }
  QString tableName = lineCreateTable_->text();
  if (tables_.contains(tableName)) {
	auto reply = QMessageBox::warning(this, "Create Error", "Table with this name already exists");
	if (reply == QMessageBox::Yes) {
	  QApplication::quit();
	}
	lineCreateTable_->clear();
	return;
  }
  tables_.append(tableName);
  boxTables_->addItem(tableName);
  lineCreateTable_->clear();
  this->cancelCreate();
//    QString command = "CREATE " + tableName;
  emit signalCreateTable(tableName);

}

void MainWindow::cancelCreate() {
  lineCreateTable_->clear();
  boxTables_->clear();
  lineCreateTable_->hide();
  buttonCreate_->hide();
  buttonCancelCreate_->hide();
  buttonCreateTable_->show();
}

void MainWindow::connectTable() {
  buttonConnectTable_->hide();
  boxTables_->addItems(tables_);
  boxTables_->show();
  buttonConnect_->show();
  buttonCancelConnect_->show();
}

void MainWindow::connectClicked() {
  QString tableName = boxTables_->currentText();
  this->cancelConnect();
//    QString command = "CONNECT " + tableName;
  emit signalConnectTable(tableName);
}

