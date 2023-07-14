#ifndef _GRAPH_H
#define _GRAPH_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>

extern "C" {
#include "smart_calc_v1.h"
}

namespace Ui {
class Graph;
}

class Graph : public QMainWindow {
  Q_OBJECT

 public:
  explicit Graph(QWidget* parent = nullptr);
  ~Graph();
  QString buffer;

 private slots:
  void replotFunc();
  void fillXY(const QString& buf, QVector<double>* x, QVector<double>* y,
              double rangeMin, double rangeMax);

 private:
  Ui::Graph* ui;
};

#endif  // _GRAPH_H
