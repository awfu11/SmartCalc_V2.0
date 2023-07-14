#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget* parent) : QMainWindow(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(replotFunc()));
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
}

Graph::~Graph() { delete ui; }

void Graph::fillXY(const QString& buf, QVector<double>* x, QVector<double>* y,
                   double rangeMin, double rangeMax) {
  double step = fabs(rangeMax - rangeMin) / 2e6;
  double res = 1.0;
  for (double value = rangeMin; value <= rangeMax; value += step) {
    if (calculatePN(buf.toLocal8Bit().data(), &res, value) == OK) {
      x->push_back(value);
      y->push_back(res);
    }
  }
}

void Graph::replotFunc() {
  double rangeMinX = 0.0, rangeMaxX = 0.0;
  double rangeMinY = 0.0, rangeMaxY = 0.0;
  if (ui->doubleSpinBox->value() < ui->doubleSpinBox_2->value()) {
    rangeMinX = ui->doubleSpinBox->value();
    rangeMaxX = ui->doubleSpinBox_2->value();
  } else if (ui->doubleSpinBox->value() == ui->doubleSpinBox_2->value()) {
    rangeMinX = ui->doubleSpinBox->value();
    rangeMaxX = ui->doubleSpinBox_2->value() + 1.0;
  } else {
    rangeMaxX = ui->doubleSpinBox->value();
    rangeMinX = ui->doubleSpinBox_2->value();
  }
  if (ui->doubleSpinBox_3->value() < ui->doubleSpinBox_4->value()) {
    rangeMinY = ui->doubleSpinBox_3->value();
    rangeMaxY = ui->doubleSpinBox_4->value();
  } else if (ui->doubleSpinBox_3->value() == ui->doubleSpinBox_4->value()) {
    rangeMinY = ui->doubleSpinBox_3->value();
    rangeMaxY = ui->doubleSpinBox_4->value() + 1.0;
  } else {
    rangeMaxY = ui->doubleSpinBox_3->value();
    rangeMinY = ui->doubleSpinBox_4->value();
  }
  QVector<double> x, y;
  fillXY(buffer, &x, &y, rangeMinX, rangeMaxX);
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDot, 4));
  ui->widget->xAxis->setRange(rangeMinX, rangeMaxX);
  ui->widget->yAxis->setRange(rangeMinY, rangeMaxY);
  ui->widget->replot();
}
