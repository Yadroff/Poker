#ifndef LOAD_H
#define LOAD_H

#include <QWidget>
#include <QMovie>

namespace Ui {
class Load;
}

class Load : public QWidget
{
    Q_OBJECT

public:
    explicit Load(QWidget *parent = nullptr);
    ~Load();

private:
    Ui::Load *ui;
    QMovie *movie_;
};

#endif // LOAD_H
