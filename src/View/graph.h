#ifndef SMARTCALC_SRC_VIEW_GRAPH_H
#define SMARTCALC_SRC_VIEW_GRAPH_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QVector>

#include "../Controller/controller.h"
#include "../QCustomPlot/qcustomplot.h"

namespace Ui {
class Graph;
}

namespace awfl {
class Graph : public QMainWindow {
  Q_OBJECT

 public:
  explicit Graph(Controller* c, QString lexem, QWidget* parent = nullptr);
  ~Graph();

 private slots:
  void replot();

 private:
  Ui::Graph* ui;
  QString lexem;
  Controller* controller;

  void fill(QVector<double>& x, QVector<double>& y, double& rangeMin,
            double& rangeMax);
};
}  // namespace awfl

#endif  // SMARTCALC_SRC_VIEW_GRAPH_H
