#include "gameui.h"
#include "ui_gameui.h"
#include <QVBoxLayout>

GameUI::GameUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameUI)
{
    ui->setupUi(this);
    ui->centralwidget->setWindowState(Qt::WindowMaximized);
    setupSeats();
}

GameUI::~GameUI()
{
    delete ui;
}

void GameUI::setupSeats()
{
    seats_.resize(8);
    // player 0
    auto *player0Coins = new QVector<QLabel*>;
    player0Coins->reserve(8);
    player0Coins->push_back(ui->Player0Stack0);
    player0Coins->push_back(ui->Player0Stack1);
    player0Coins->push_back(ui->Player0Stack2);
    player0Coins->push_back(ui->Player0Stack3);
    player0Coins->push_back(ui->Player0Stack4);
    player0Coins->push_back(ui->Player0Stack5);
    player0Coins->push_back(ui->Player0Stack6);
    player0Coins->push_back(ui->Player0Stack7);
    auto *player0Cards = new QVector<QLabel*>;
    player0Cards->reserve(2);
    player0Cards->push_back(ui->Player0Card1);
    player0Cards->push_back(ui->Player0Card2);
    auto *player0Name = ui->Player0Name;
    auto *player0Money = ui->Player0ChipCount;
    auto *player0Button = ui->buttonSitInSeat0;
    auto *player0Place = ui->placeholder0;
    seats_.push_back(new Seat(player0Coins, player0Cards, player0Place, player0Name, player0Money, player0Button));
    // player 1
    auto *player1Coins = new QVector<QLabel*>;
    player1Coins->reserve(8);
    player1Coins->push_back(ui->Player1Stack0);
    player1Coins->push_back(ui->Player1Stack1);
    player1Coins->push_back(ui->Player1Stack2);
    player1Coins->push_back(ui->Player1Stack3);
    player1Coins->push_back(ui->Player1Stack4);
    player1Coins->push_back(ui->Player1Stack5);
    player1Coins->push_back(ui->Player1Stack6);
    player1Coins->push_back(ui->Player1Stack7);
    auto *player1Cards = new QVector<QLabel*>;
    player1Cards->reserve(2);
    player1Cards->push_back(ui->Player1Card1);
    player1Cards->push_back(ui->Player1Card2);
    auto *player1Name = ui->Player1Name;
    auto *player1Money = ui->Player1ChipCount;
    auto *player1Button = ui->buttonSitInSeat1;
    auto *player1Place = ui->placeholder1;
    seats_.push_back(new Seat(player1Coins, player1Cards, player1Place, player1Name, player1Money, player1Button));
    //player 2
    auto *player2Coins = new QVector<QLabel*>;
    player2Coins->reserve(8);
    player2Coins->push_back(ui->Player2Stack0);
    player2Coins->push_back(ui->Player2Stack1);
    player2Coins->push_back(ui->Player2Stack2);
    player2Coins->push_back(ui->Player2Stack3);
    player2Coins->push_back(ui->Player2Stack4);
    player2Coins->push_back(ui->Player2Stack5);
    player2Coins->push_back(ui->Player2Stack6);
    player2Coins->push_back(ui->Player2Stack7);
    auto *player2Cards = new QVector<QLabel*>;
    player2Cards->reserve(2);
    player2Cards->push_back(ui->Player2Card1);
    player2Cards->push_back(ui->Player2Card2);
    auto *player2Name = ui->Player2Name;
    auto *player2Money = ui->Player2ChipCount;
    auto *player2Button = ui->buttonSitInSeat2;
    auto *player2Place = ui->placeholder2;
    seats_.push_back(new Seat(player2Coins, player2Cards, player2Place, player2Name, player2Money, player2Button));
    //player 3
    auto *player3Coins = new QVector<QLabel*>;
    player3Coins->reserve(8);
    player3Coins->push_back(ui->Player3Stack0);
    player3Coins->push_back(ui->Player3Stack1);
    player3Coins->push_back(ui->Player3Stack2);
    player3Coins->push_back(ui->Player3Stack3);
    player3Coins->push_back(ui->Player3Stack4);
    player3Coins->push_back(ui->Player3Stack5);
    player3Coins->push_back(ui->Player3Stack6);
    player3Coins->push_back(ui->Player3Stack7);
    auto *player3Cards = new QVector<QLabel*>;
    player3Cards->reserve(2);
    player3Cards->push_back(ui->Player3Card1);
    player3Cards->push_back(ui->Player3Card2);
    auto *player3Name = ui->Player3Name;
    auto *player3Money = ui->Player3ChipCount;
    auto *player3Button = ui->buttonSitInSeat3;
    auto *player3Place = ui->placeholder3;
    seats_.push_back(new Seat(player3Coins, player3Cards, player3Place, player3Name, player3Money, player3Button));
    //player 4
    auto *player4Coins = new QVector<QLabel*>;
    player4Coins->reserve(8);
    player4Coins->push_back(ui->Player4Stack0);
    player4Coins->push_back(ui->Player4Stack1);
    player4Coins->push_back(ui->Player4Stack2);
    player4Coins->push_back(ui->Player4Stack3);
    player4Coins->push_back(ui->Player4Stack4);
    player4Coins->push_back(ui->Player4Stack5);
    player4Coins->push_back(ui->Player4Stack6);
    player4Coins->push_back(ui->Player4Stack7);
    auto *player4Cards = new QVector<QLabel*>;
    player4Cards->reserve(2);
    player4Cards->push_back(ui->Player4Card1);
    player4Cards->push_back(ui->Player4Card2);
    auto *player4Name = ui->Player4Name;
    auto *player4Money = ui->Player4ChipCount;
    auto *player4Button = ui->buttonSitInSeat4;
    auto *player4Place = ui->placeholder4;
    seats_.push_back(new Seat(player4Coins, player4Cards, player4Place, player4Name, player4Money, player4Button));
    //player 5
    auto *player5Coins = new QVector<QLabel*>;
    player5Coins->reserve(8);
    player5Coins->push_back(ui->Player5Stack0);
    player5Coins->push_back(ui->Player5Stack1);
    player5Coins->push_back(ui->Player5Stack2);
    player5Coins->push_back(ui->Player5Stack3);
    player5Coins->push_back(ui->Player5Stack4);
    player5Coins->push_back(ui->Player5Stack5);
    player5Coins->push_back(ui->Player5Stack6);
    player5Coins->push_back(ui->Player5Stack7);
    auto *player5Cards = new QVector<QLabel*>;
    player5Cards->reserve(2);
    player5Cards->push_back(ui->Player5Card1);
    player5Cards->push_back(ui->Player5Card2);
    auto *player5Name = ui->Player5Name;
    auto *player5Money = ui->Player5ChipCount;
    auto *player5Button = ui->buttonSitInSeat5;
    auto *player5Place = ui->placeholder5;
    seats_.push_back(new Seat(player5Coins, player5Cards, player5Place, player5Name, player5Money, player5Button));
    //player 6
    auto *player6Coins = new QVector<QLabel*>;
    player6Coins->reserve(8);
    player6Coins->push_back(ui->Player6Stack0);
    player6Coins->push_back(ui->Player6Stack1);
    player6Coins->push_back(ui->Player6Stack2);
    player6Coins->push_back(ui->Player6Stack3);
    player6Coins->push_back(ui->Player6Stack4);
    player6Coins->push_back(ui->Player6Stack5);
    player6Coins->push_back(ui->Player6Stack6);
    player6Coins->push_back(ui->Player6Stack7);
    auto *player6Cards = new QVector<QLabel*>;
    player6Cards->reserve(2);
    player6Cards->push_back(ui->Player6Card1);
    player6Cards->push_back(ui->Player6Card2);
    auto *player6Name = ui->Player6Name;
    auto *player6Money = ui->Player6ChipCount;
    auto *player6Button = ui->buttonSitInSeat6;
    auto *player6Place = ui->placeholder6;
    seats_.push_back(new Seat(player6Coins, player6Cards, player6Place, player6Name, player6Money, player6Button));
    //player 7
    auto *player7Coins = new QVector<QLabel*>;
    player7Coins->reserve(8);
    player7Coins->push_back(ui->Player7Stack0);
    player7Coins->push_back(ui->Player7Stack1);
    player7Coins->push_back(ui->Player7Stack2);
    player7Coins->push_back(ui->Player7Stack3);
    player7Coins->push_back(ui->Player7Stack4);
    player7Coins->push_back(ui->Player7Stack5);
    player7Coins->push_back(ui->Player7Stack6);
    player7Coins->push_back(ui->Player7Stack7);
    auto *player7Cards = new QVector<QLabel*>;
    player7Cards->reserve(2);
    player7Cards->push_back(ui->Player7Card1);
    player7Cards->push_back(ui->Player7Card2);
    auto *player7Name = ui->Player7Name;
    auto *player7Money = ui->Player7ChipCount;
    auto *player7Button = ui->buttonSitInSeat7;
    auto *player7Place = ui->placeholder7;
    seats_.push_back(new Seat(player7Coins, player7Cards, player7Place, player7Name, player7Money, player7Button));
}
