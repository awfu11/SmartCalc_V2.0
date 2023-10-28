#include <QApplication>

#include "View/view.h"

int main(int argc, char *argv[]) {
  using namespace awfl;
  QApplication a(argc, argv);

  Model model;
  Controller controller(&model);
  View w(&controller);

  w.show();
  w.setWindowTitle("SmartCalc v2.0");
  return a.exec();
}
