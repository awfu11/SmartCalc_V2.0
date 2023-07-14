#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QMainWindow>

extern "C" {
#include "credit.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class CreditCalc;
}
QT_END_NAMESPACE

class CreditCalc : public QMainWindow {
  Q_OBJECT

 public:
  CreditCalc(QWidget* parent = nullptr);
  ~CreditCalc();

 private slots:
  void cCalc();

 private:
  Ui::CreditCalc* ui;
};
#endif  // CREDITCALC_H
