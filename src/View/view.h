#ifndef SMARTCALC_SRC_VIEW_VIEW_H
#define SMARTCALC_SRC_VIEW_VIEW_H

#include <QChar>
#include <QInputDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>

#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace awfl {
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller* c, QWidget* parent = nullptr);
  ~View();

 private slots:
  void clearLabel();
  void digitsOutput();
  void variableOrConstOutput();
  void functionOutput();
  void operatorsOutput();
  void dotOutput();
  void bracketOutput();
  void equalOutput();
  void plotFunction();

 private:
  Ui::View* ui;
  Graph* wind = nullptr;
  Controller* controller;

  void treatLexemFCV();
  bool validLexem(QString& lexem);
  bool isNotOperator(QChar& c);
  void keyPressEvent(QKeyEvent* event);
};
}  // namespace awfl

#endif  // SMARTCALC_SRC_VIEW_VIEW_H
