#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMediaPlayer>
#include "dialogwindow.h"
#include "button.h"
#include <iostream>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStringList tables;

signals:
   void needToSend(const QString &command);
private slots:\
    // create
    void createTable();
    void createClicked();
    void cancelCreate();

    //connect
    void connectTable();
    void connectClicked();
    void cancelConnect();

    //others
    void exitMenu();
    void help();
private:
    void setupUI();
    Button *buttonCreateTable_;
    Button *buttonCreate_;
    Button *buttonCancelCreate_;
    QLineEdit *lineCreateTable_;

    Button *buttonConnectTable_;
    Button *buttonConnect_;
    Button *buttonCancelConnect_;
    QComboBox *boxTables_;

    Button *buttonHelp_;
    Button *exit_;

    DialogWindow *createTableWindow_;
    QMediaPlayer *mediaPlayer_;

};
#endif // MAINWINDOW_H
