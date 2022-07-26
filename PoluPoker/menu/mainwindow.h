#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMediaPlayer>
#include "button.h"
#include <iostream>

class MainWindow : public QWidget {
 Q_OBJECT

 public:
  explicit MainWindow(const QStringList &tables, QWidget *parent = nullptr);
  ~MainWindow();
 public slots:
  void updateTablesList(const QStringList &tables);
 signals:
  void signalCreateTable(const QString &name);
  void signalConnectTable(const QString &name);
  void signalUpdateTables();
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

  QMediaPlayer *mediaPlayer_;

};
#endif // MAINWINDOW_H
