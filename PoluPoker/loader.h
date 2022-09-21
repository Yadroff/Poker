#ifndef LOADER_H
#define LOADER_H

#include <QMainWindow>
#include <QMovie>

namespace Ui {
class Loader;
}

class Loader : public QMainWindow {
 Q_OBJECT

 public:
  explicit Loader(QWidget *parent = nullptr);
  ~Loader();
  void setStatus(const QString &status);
 private:
  Ui::Loader *ui;
  QMovie *movie_;
};

#endif // LOADER_H
