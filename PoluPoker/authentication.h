#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class Authentication;
}

class Authentication : public QMainWindow
{
    Q_OBJECT

public:
    explicit Authentication(QWidget *parent = nullptr);
    ~Authentication();

private slots:
    void on_buttonRegister_clicked();

    void on_buttonLogin_clicked();

private:
    Ui::Authentication *ui;
};

#endif // AUTHENTICATION_H
