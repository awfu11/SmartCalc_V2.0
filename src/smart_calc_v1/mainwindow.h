#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <creditcalc.h>
#include <graph.h>

#include <QInputDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QVector>

extern "C" {
#include "smart_calc_v1.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void allclearLabel();
  void constOutput();
  void digitsOutput();
  void operatorsOutput();
  void dotOutput();
  void bracketOutput();
  void functionOutput();
  void variableOutput();
  void equalOutput();
  void plotFunction();
  void creditC();

 private:
  Ui::MainWindow *ui;
  Graph *wind;
  CreditCalc *cc;

 protected:
  void keyPressEvent(QKeyEvent *event);
};
#endif  // _MAINWINDOW_H
