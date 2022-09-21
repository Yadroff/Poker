#include <QApplication>
#include "screencontroller.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  ScreenController scr;
  return a.exec();
}
