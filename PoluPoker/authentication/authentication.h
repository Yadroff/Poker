#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QMainWindow>
#include <QMessageBox>

const QString KEY_VERNAM = "EVTIQWXQVVOPMCXREPYZ";
const int KEY_SIZE = KEY_VERNAM.size();

namespace Ui {
class Authentication;
}

class Authentication : public QMainWindow {
 Q_OBJECT

 public:
  explicit Authentication(QWidget *parent = nullptr);
  ~Authentication();
  void setEnabled(const bool &status);
//    void load();
//    void stopLoad();
 private:
//        Load *load_;
 signals:
  void needToSend(const QString &command);
  void changeLogin(const QString &login);
 private slots:
  void on_buttonRegister_clicked();

  void on_buttonLogin_clicked();

 private:
  Ui::Authentication *ui;

  bool isValidString(QString &password);
  void transformString(QString &string);
};

#endif // AUTHENTICATION_H
