#include "graph.h"

#include "ui_graph.h"

namespace awfl {
Graph::Graph(Controller* c, QString lexem, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::Graph), controller(c) {
  ui->setupUi(this);
  this->lexem = lexem;

  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(replot()));
  replot();

  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
}

Graph::~Graph() { delete ui; }

void Graph::fill(QVector<double>& x, QVector<double>& y, double& rangeMin,
                 double& rangeMax) {
  double step = std::abs(rangeMax - rangeMin) / 1e5;
  x.reserve(1e5 + 1);
  y.reserve(1e5 + 1);
  for (double value = rangeMin; value <= rangeMax; value += step) {
    auto calc = controller->calculate(lexem.toStdString(), value);
    if (calc.first == OK) {
      x.push_back(value);
      y.push_back(calc.second);
    }
  }
}

void Graph::replot() {
  double rangeMinX = ui->doubleSpinBoxXmin->value();
  double rangeMaxX = ui->doubleSpinBoxXmax->value();
  double rangeMinY = ui->doubleSpinBoxYmin->value();
  double rangeMaxY = ui->doubleSpinBoxYmax->value();

  if (rangeMaxX < rangeMinX) {
    std::swap(rangeMaxX, rangeMinX);
    ui->doubleSpinBoxXmax->setValue(rangeMaxX);
    ui->doubleSpinBoxXmin->setValue(rangeMinX);
  } else if (rangeMaxX == rangeMinX) {
    rangeMaxX += 1.0;
    ui->doubleSpinBoxXmax->setValue(rangeMaxX);
  }

  if (rangeMaxY < rangeMinY) {
    std::swap(rangeMaxY, rangeMinY);
    ui->doubleSpinBoxYmax->setValue(rangeMaxY);
    ui->doubleSpinBoxYmin->setValue(rangeMinY);
  } else if (rangeMaxY == rangeMinY) {
    rangeMaxY += 1.0;
    ui->doubleSpinBoxYmax->setValue(rangeMaxY);
  }

  QVector<double> x, y;
  fill(x, y, rangeMinX, rangeMaxX);

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

}  // namespace awfl
