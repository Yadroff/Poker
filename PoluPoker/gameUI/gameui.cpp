#include "gameui.h"
#include "ui_gameui.h"

#include <QMessageBox>
#include <iostream>

GameUI::GameUI(const QString &name, const QString &myName, const int &bet, const int &pot, QWidget *parent)
	:
	QMainWindow(parent), ui(new Ui::GameUI), bet_(bet), pot_(pot), name_(name) {
  setWindowTitle(name);
  std::cout << windowTitle().toStdString() << std::endl;
  me_ = new Player(myName, this);
  ui->setupUi(this);
  ui->centralwidget->setWindowState(Qt::WindowMaximized);
  setupSeats();
  setupCards();
  hideBet();
//    test();
}

GameUI::~GameUI() {
  delete ui;
}

void
GameUI::test() {
  players_.push_back(new Player("TEST", seats_[0]));
  bet_ = 500;
  pot_ = 500;
  showBetOnTable();
  bet();
}

void
GameUI::showGUI() {
  ui->labelCardHolder->show();
}

void
GameUI::showBetOnTable() {
  ui->labelPot->show();
  ui->labelPotHolder->show();
  ui->labelPot->setText(QString::number(pot_));
}

void
GameUI::setupSeats() {
  // player 0
  auto *player0Coins = new QVector<QLabel *>;
  player0Coins->reserve(8);
  player0Coins->push_back(ui->Player0Stack0);
  player0Coins->push_back(ui->Player0Stack1);
  player0Coins->push_back(ui->Player0Stack2);
  player0Coins->push_back(ui->Player0Stack3);
  player0Coins->push_back(ui->Player0Stack4);
  player0Coins->push_back(ui->Player0Stack5);
  player0Coins->push_back(ui->Player0Stack6);
  player0Coins->push_back(ui->Player0Stack7);
  auto *player0Cards = new QVector<QLabel *>;
  player0Cards->reserve(2);
  player0Cards->push_back(ui->Player0Card1);
  player0Cards->push_back(ui->Player0Card2);
  auto *player0Name = ui->Player0Name;
  auto *player0Money = ui->Player0ChipCount;
  auto *player0Button = ui->buttonSitInSeat0;
  auto *player0Place = ui->placeholder0;
  seats_.push_back(new Seat(player0Coins, player0Cards, player0Place, player0Name, player0Money, player0Button));
  // player 1
  auto *player1Coins = new QVector<QLabel *>;
  player1Coins->reserve(8);
  player1Coins->push_back(ui->Player1Stack0);
  player1Coins->push_back(ui->Player1Stack1);
  player1Coins->push_back(ui->Player1Stack2);
  player1Coins->push_back(ui->Player1Stack3);
  player1Coins->push_back(ui->Player1Stack4);
  player1Coins->push_back(ui->Player1Stack5);
  player1Coins->push_back(ui->Player1Stack6);
  player1Coins->push_back(ui->Player1Stack7);
  auto *player1Cards = new QVector<QLabel *>;
  player1Cards->reserve(2);
  player1Cards->push_back(ui->Player1Card1);
  player1Cards->push_back(ui->Player1Card2);
  auto *player1Name = ui->Player1Name;
  auto *player1Money = ui->Player1ChipCount;
  auto *player1Button = ui->buttonSitInSeat1;
  auto *player1Place = ui->placeholder1;
  seats_.push_back(new Seat(player1Coins, player1Cards, player1Place, player1Name, player1Money, player1Button));
  //player 2
  auto *player2Coins = new QVector<QLabel *>;
  player2Coins->reserve(8);
  player2Coins->push_back(ui->Player2Stack0);
  player2Coins->push_back(ui->Player2Stack1);
  player2Coins->push_back(ui->Player2Stack2);
  player2Coins->push_back(ui->Player2Stack3);
  player2Coins->push_back(ui->Player2Stack4);
  player2Coins->push_back(ui->Player2Stack5);
  player2Coins->push_back(ui->Player2Stack6);
  player2Coins->push_back(ui->Player2Stack7);
  auto *player2Cards = new QVector<QLabel *>;
  player2Cards->reserve(2);
  player2Cards->push_back(ui->Player2Card1);
  player2Cards->push_back(ui->Player2Card2);
  auto *player2Name = ui->Player2Name;
  auto *player2Money = ui->Player2ChipCount;
  auto *player2Button = ui->buttonSitInSeat2;
  auto *player2Place = ui->placeholder2;
  seats_.push_back(new Seat(player2Coins, player2Cards, player2Place, player2Name, player2Money, player2Button));
  //player 3
  auto *player3Coins = new QVector<QLabel *>;
  player3Coins->reserve(8);
  player3Coins->push_back(ui->Player3Stack0);
  player3Coins->push_back(ui->Player3Stack1);
  player3Coins->push_back(ui->Player3Stack2);
  player3Coins->push_back(ui->Player3Stack3);
  player3Coins->push_back(ui->Player3Stack4);
  player3Coins->push_back(ui->Player3Stack5);
  player3Coins->push_back(ui->Player3Stack6);
  player3Coins->push_back(ui->Player3Stack7);
  auto *player3Cards = new QVector<QLabel *>;
  player3Cards->reserve(2);
  player3Cards->push_back(ui->Player3Card1);
  player3Cards->push_back(ui->Player3Card2);
  auto *player3Name = ui->Player3Name;
  auto *player3Money = ui->Player3ChipCount;
  auto *player3Button = ui->buttonSitInSeat3;
  auto *player3Place = ui->placeholder3;
  seats_.push_back(new Seat(player3Coins, player3Cards, player3Place, player3Name, player3Money, player3Button));
  //player 4
  auto *player4Coins = new QVector<QLabel *>;
  player4Coins->reserve(8);
  player4Coins->push_back(ui->Player4Stack0);
  player4Coins->push_back(ui->Player4Stack1);
  player4Coins->push_back(ui->Player4Stack2);
  player4Coins->push_back(ui->Player4Stack3);
  player4Coins->push_back(ui->Player4Stack4);
  player4Coins->push_back(ui->Player4Stack5);
  player4Coins->push_back(ui->Player4Stack6);
  player4Coins->push_back(ui->Player4Stack7);
  auto *player4Cards = new QVector<QLabel *>;
  player4Cards->reserve(2);
  player4Cards->push_back(ui->Player4Card1);
  player4Cards->push_back(ui->Player4Card2);
  auto *player4Name = ui->Player4Name;
  auto *player4Money = ui->Player4ChipCount;
  auto *player4Button = ui->buttonSitInSeat4;
  auto *player4Place = ui->placeholder4;
  seats_.push_back(new Seat(player4Coins, player4Cards, player4Place, player4Name, player4Money, player4Button));
  //player 5
  auto *player5Coins = new QVector<QLabel *>;
  player5Coins->reserve(8);
  player5Coins->push_back(ui->Player5Stack0);
  player5Coins->push_back(ui->Player5Stack1);
  player5Coins->push_back(ui->Player5Stack2);
  player5Coins->push_back(ui->Player5Stack3);
  player5Coins->push_back(ui->Player5Stack4);
  player5Coins->push_back(ui->Player5Stack5);
  player5Coins->push_back(ui->Player5Stack6);
  player5Coins->push_back(ui->Player5Stack7);
  auto *player5Cards = new QVector<QLabel *>;
  player5Cards->reserve(2);
  player5Cards->push_back(ui->Player5Card1);
  player5Cards->push_back(ui->Player5Card2);
  auto *player5Name = ui->Player5Name;
  auto *player5Money = ui->Player5ChipCount;
  auto *player5Button = ui->buttonSitInSeat5;
  auto *player5Place = ui->placeholder5;
  seats_.push_back(new Seat(player5Coins, player5Cards, player5Place, player5Name, player5Money, player5Button));
  //player 6
  auto *player6Coins = new QVector<QLabel *>;
  player6Coins->reserve(8);
  player6Coins->push_back(ui->Player6Stack0);
  player6Coins->push_back(ui->Player6Stack1);
  player6Coins->push_back(ui->Player6Stack2);
  player6Coins->push_back(ui->Player6Stack3);
  player6Coins->push_back(ui->Player6Stack4);
  player6Coins->push_back(ui->Player6Stack5);
  player6Coins->push_back(ui->Player6Stack6);
  player6Coins->push_back(ui->Player6Stack7);
  auto *player6Cards = new QVector<QLabel *>;
  player6Cards->reserve(2);
  player6Cards->push_back(ui->Player6Card1);
  player6Cards->push_back(ui->Player6Card2);
  auto *player6Name = ui->Player6Name;
  auto *player6Money = ui->Player6ChipCount;
  auto *player6Button = ui->buttonSitInSeat6;
  auto *player6Place = ui->placeholder6;
  seats_.push_back(new Seat(player6Coins, player6Cards, player6Place, player6Name, player6Money, player6Button));
  //player 7
  auto *player7Coins = new QVector<QLabel *>;
  player7Coins->reserve(8);
  player7Coins->push_back(ui->Player7Stack0);
  player7Coins->push_back(ui->Player7Stack1);
  player7Coins->push_back(ui->Player7Stack2);
  player7Coins->push_back(ui->Player7Stack3);
  player7Coins->push_back(ui->Player7Stack4);
  player7Coins->push_back(ui->Player7Stack5);
  player7Coins->push_back(ui->Player7Stack6);
  player7Coins->push_back(ui->Player7Stack7);
  auto *player7Cards = new QVector<QLabel *>;
  player7Cards->reserve(2);
  player7Cards->push_back(ui->Player7Card1);
  player7Cards->push_back(ui->Player7Card2);
  auto *player7Name = ui->Player7Name;
  auto *player7Money = ui->Player7ChipCount;
  auto *player7Button = ui->buttonSitInSeat7;
  auto *player7Place = ui->placeholder7;
  seats_.push_back(new Seat(player7Coins, player7Cards, player7Place, player7Name, player7Money, player7Button));
}

void
GameUI::setupCards() {
  cards_.resize(5);
  cards_.push_back(ui->labelCommunityCard1);
  ui->labelCommunityCard1->hide();
  cards_.push_back(ui->labelCommunityCard2);
  ui->labelCommunityCard2->hide();
  cards_.push_back(ui->labelCommunityCard3);
  ui->labelCommunityCard3->hide();
  cards_.push_back(ui->labelCommunityCard4);
  ui->labelCommunityCard4->hide();
  cards_.push_back(ui->labelCommunityCard5);
  ui->labelCommunityCard5->hide();
  ui->labelPot->hide();
  ui->labelPotHolder->hide();
  ui->labelPlayerCard1->hide();
  ui->labelPlayerCard2->hide();
  ui->labelCardHolder->hide();
}

void
GameUI::bet() {
  ui->messageBrowser->append(QString("System: Current bet is %1").arg(bet_));
  ui->labelButtonHolder->show();
  ui->buttonCall->show();
  ui->buttonFold->show();
  ui->buttonBet->show();
}

void
GameUI::hideBet() {
  ui->labelButtonHolder->hide();
  ui->buttonBet->hide();
  ui->buttonCall->hide();
  ui->buttonCancel->hide();
  ui->buttonDecrementBet->hide();
  ui->buttonIncrementBet->hide();
  ui->buttonFold->hide();
  ui->buttonSubmit->hide();
  ui->horizontalBetSlider->hide();
  ui->inputBet->hide();
}

void
GameUI::on_buttonSitInSeat0_clicked() {
  if (seats_[0]->isAvailable()) {
	me_->changeSeat(seats_[0]);
	showGUI();
	//TODO: отправить на сервер изменение места
//	emit changeSeat(0);
	std::cout << "TABLE NAME: " << name_.toStdString() << " MY NAME: " << me_->name().toStdString() << std::endl;
	emit send("CHANGE_SEAT" + SEPARATOR + name_ + SEPARATOR + me_->name() + SEPARATOR + "0");
  } else {
	QMessageBox::critical(this, "ERROR", "Choosen seat is taken");
  }
}

void
GameUI::on_buttonSitInSeat1_clicked() {
  if (seats_[1]->isAvailable()) {
	me_->changeSeat(seats_[1]);
	showGUI();
//	emit changeSeat(1);
	std::cout << "TABLE NAME: " << name_.toStdString() << " MY NAME: " << me_->name().toStdString() << std::endl;
	emit send("CHANGE_SEAT" + SEPARATOR + name_ + SEPARATOR + me_->name() + SEPARATOR + "1");

  } else {
	QMessageBox::critical(this, "ERROR", "Choosen seat is taken");
  }
}

void
GameUI::on_buttonSitInSeat2_clicked() {
  if (seats_[2]->isAvailable()) {
	me_->changeSeat(seats_[2]);
//	emit changeSeat(2);
	std::cout << "TABLE NAME: " << name_.toStdString() << " MY NAME: " << me_->name().toStdString() << std::endl;
	emit send("CHANGE_SEAT" + SEPARATOR + name_ + SEPARATOR + me_->name() + SEPARATOR + "2");
  } else {
	QMessageBox::critical(this, "ERROR", "Choosen seat is taken");
  }
}

void
GameUI::on_buttonSitInSeat3_clicked() {
  if (seats_[3]->isAvailable()) {
	me_->changeSeat(seats_[3]);
	showGUI();
//	emit changeSeat(3);
	std::cout << "TABLE NAME: " << name_.toStdString() << " MY NAME: " << me_->name().toStdString() << std::endl;
	emit send("CHANGE_SEAT" + SEPARATOR + name_ + SEPARATOR + me_->name() + SEPARATOR + "3");
  } else {
	QMessageBox::critical(this, "ERROR", "Choosen seat is taken");
  }
}

void
GameUI::on_buttonSitInSeat4_clicked() {
  if (seats_[4]->isAvailable()) {
	me_->changeSeat(seats_[4]);
	showGUI();
//	emit changeSeat(4);
	std::cout << "TABLE NAME: " << name_.toStdString() << " MY NAME: " << me_->name().toStdString() << std::endl;
	emit send("CHANGE_SEAT" + SEPARATOR + name_ + SEPARATOR + me_->name() + SEPARATOR + "4");
  } else {
	QMessageBox::critical(this, "ERROR", "Choosen seat is taken");
  }
}

void
GameUI::on_buttonSitInSeat5_clicked() {
  if (seats_[5]->isAvailable()) {
	me_->changeSeat(seats_[5]);
	showGUI();
//	emit changeSeat(5);
	std::cout << "TABLE NAME: " << name_.toStdString() << " MY NAME: " << me_->name().toStdString() << std::endl;
	emit send("CHANGE_SEAT" + SEPARATOR + name_ + SEPARATOR + me_->name() + SEPARATOR + "5");
	startGame();
	test();
  } else {
	QMessageBox::critical(this, "ERROR", "Choosen seat is taken");
  }
}

void
GameUI::on_buttonSitInSeat6_clicked() {
  if (seats_[6]->isAvailable()) {
	me_->changeSeat(seats_[6]);
	showGUI();
//	emit changeSeat(6);
	std::cout << "TABLE NAME: " << name_.toStdString() << " MY NAME: " << me_->name().toStdString() << std::endl;
	emit send("CHANGE_SEAT" + SEPARATOR + name_ + SEPARATOR + me_->name() + SEPARATOR + "6");
  } else {
	QMessageBox::critical(this, "ERROR", "Choosen seat is taken");
  }
}

void
GameUI::on_buttonSitInSeat7_clicked() {
  if (seats_[7]->isAvailable()) {
	me_->changeSeat(seats_[7]);
	showGUI();
//	emit changeSeat(7);
	std::cout << "TABLE NAME: " << name_.toStdString() << " MY NAME: " << me_->name().toStdString() << std::endl;
	emit send("CHANGE_SEAT" + SEPARATOR + name_ + SEPARATOR + me_->name() + SEPARATOR + "7");
  } else {
	QMessageBox::critical(this, "ERROR", "Choosen seat is taken");
  }
}

void
GameUI::on_buttonFold_clicked() {
  ui->messageBrowser->append("System: You fold");
  hideBet();
  //TODO: отправить на сервер fold
  emit send("FOLD" + SEPARATOR + name_ + SEPARATOR + me_->name());
  me_->clearCards();
}

void
GameUI::on_buttonBet_clicked() {
  ui->buttonBet->hide();
  ui->buttonCall->hide();
  ui->buttonFold->hide();
  ui->buttonDecrementBet->show();
  ui->buttonIncrementBet->show();
  ui->buttonCancel->show();
  ui->buttonSubmit->show();
  ui->inputBet->show();
  ui->horizontalBetSlider->show();
  ui->inputBet->setText(QString::number(bet_));
}

void
GameUI::on_horizontalBetSlider_sliderMoved(int position) {
  ui->inputBet->setText(QString::number((me_->money() - bet_) / 100 * position + bet_));
}

void
GameUI::on_buttonIncrementBet_clicked() {
  int curValue = ui->horizontalBetSlider->value();
  if (curValue != 100) {
	ui->horizontalBetSlider->setValue(++curValue);

  }
}

void
GameUI::on_horizontalBetSlider_valueChanged(int value) {
  ui->horizontalBetSlider->setSliderPosition(value);
  emit ui->horizontalBetSlider->sliderMoved(value);
}

void
GameUI::on_buttonDecrementBet_clicked() {
  int curValue = ui->horizontalBetSlider->value();
  if (curValue > 0) {
	ui->horizontalBetSlider->setValue(--curValue);
  }
}

void
GameUI::on_buttonCancel_clicked() {
  hideBet();
  bet();
}

void
GameUI::on_buttonSubmit_clicked() {
  bet_ = ui->inputBet->text().toInt();
  pot_ += bet_;
  showBetOnTable();
  ui->messageBrowser->append(QString("System: You set new bet: %1").arg(bet_));
  me_->bet(bet_);
  hideBet();
  //TODO: отправить на сервер изменение ставки
  emit send("BET" + SEPARATOR + name_ + SEPARATOR + me_->name() + SEPARATOR + QString::number(bet_));
//  emit bet(bet_);
}

void
GameUI::on_buttonCall_clicked() {
  me_->bet(bet_);
  pot_ += bet_;
  ui->messageBrowser->append(QString("System: You called bet: %1").arg(bet_));
  showBetOnTable();
  hideBet();
  //TODO: отправить на сервер call
  emit send("CALL" + SEPARATOR + name_ + SEPARATOR + me_->name());
//  emit call();
}

void
GameUI::on_messageBox_editingFinished() {
  QString text = ui->messageBox->text();
  if (text.isEmpty()) {
	return;
  }
  ui->messageBrowser->append("You: " + text);
  ui->messageBox->clear();
  //TODO: отправить на сервер сообщение в чат
  emit send("CHAT" + SEPARATOR + this->name_ + SEPARATOR + me_->name() + SEPARATOR + text);
}

void
GameUI::startGame() {
  ui->labelWeclomeText->hide();
  for (auto seat : seats_) {
	if (seat->isAvailable()) {
	  seat->hideAll();
	}
  }
  ui->labelBottomLeft->hide();
  ui->labelBottomRight->hide();
}
void
GameUI::addPlayer(const QString &name, const int &seat, const int &money, const int &cards) {
  auto player = new Player(name, money, seats_[seat]);
  for (int i = 0; i < cards; ++i) {
	player->giveCard();
  }
  players_.push_back(player);
}
void GameUI::chatMessage(const QString &message) {
  ui->messageBrowser->append(message);
}

