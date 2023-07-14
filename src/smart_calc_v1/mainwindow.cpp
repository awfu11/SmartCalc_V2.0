#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->label->setText("");
  ui->label_2->setText("");

  connect(ui->button_0, SIGNAL(clicked()), this, SLOT(digitsOutput()));
  connect(ui->button_1, SIGNAL(clicked()), this, SLOT(digitsOutput()));
  connect(ui->button_2, SIGNAL(clicked()), this, SLOT(digitsOutput()));
  connect(ui->button_3, SIGNAL(clicked()), this, SLOT(digitsOutput()));
  connect(ui->button_4, SIGNAL(clicked()), this, SLOT(digitsOutput()));
  connect(ui->button_5, SIGNAL(clicked()), this, SLOT(digitsOutput()));
  connect(ui->button_6, SIGNAL(clicked()), this, SLOT(digitsOutput()));
  connect(ui->button_7, SIGNAL(clicked()), this, SLOT(digitsOutput()));
  connect(ui->button_8, SIGNAL(clicked()), this, SLOT(digitsOutput()));
  connect(ui->button_9, SIGNAL(clicked()), this, SLOT(digitsOutput()));

  connect(ui->button_variable, SIGNAL(clicked()), this, SLOT(variableOutput()));

  connect(ui->button_e, SIGNAL(clicked()), this, SLOT(constOutput()));
  connect(ui->button_pi, SIGNAL(clicked()), this, SLOT(constOutput()));

  connect(ui->button_allclear, SIGNAL(clicked()), this, SLOT(allclearLabel()));

  connect(ui->button_dot, SIGNAL(clicked()), this, SLOT(dotOutput()));

  connect(ui->button_plus, SIGNAL(clicked()), this, SLOT(operatorsOutput()));
  connect(ui->button_minus, SIGNAL(clicked()), this, SLOT(operatorsOutput()));
  connect(ui->button_mult, SIGNAL(clicked()), this, SLOT(operatorsOutput()));
  connect(ui->button_div, SIGNAL(clicked()), this, SLOT(operatorsOutput()));
  connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(operatorsOutput()));
  connect(ui->button_pow, SIGNAL(clicked()), this, SLOT(operatorsOutput()));

  connect(ui->button_leftb, SIGNAL(clicked()), this, SLOT(bracketOutput()));
  connect(ui->button_rightb, SIGNAL(clicked()), this, SLOT(bracketOutput()));

  connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(functionOutput()));
  connect(ui->button_asin, SIGNAL(clicked()), this, SLOT(functionOutput()));
  connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(functionOutput()));
  connect(ui->button_acos, SIGNAL(clicked()), this, SLOT(functionOutput()));
  connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(functionOutput()));
  connect(ui->button_atan, SIGNAL(clicked()), this, SLOT(functionOutput()));
  connect(ui->button_sqrt, SIGNAL(clicked()), this, SLOT(functionOutput()));
  connect(ui->button_ln, SIGNAL(clicked()), this, SLOT(functionOutput()));
  connect(ui->button_log, SIGNAL(clicked()), this, SLOT(functionOutput()));

  connect(ui->button_eq, SIGNAL(clicked()), this, SLOT(equalOutput()));

  connect(ui->button_plot, SIGNAL(clicked()), this, SLOT(plotFunction()));

  connect(ui->creditButton, SIGNAL(clicked()), this, SLOT(creditC()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digitsOutput() {
  QPushButton *button = (QPushButton *)sender();
  QString lexem = ui->label->text();
  int length = lexem.length();
  if (length > 0 && (lexem[length - 1] == 'y' || lexem[length - 1] == 'r' ||
                     lexem[length - 1] == 'l' || lexem[length - 1] == 'h')) {
    allclearLabel();
    length = 0;
    lexem = ui->label->text();
  }
  if (length > 0) {
    if (lexem[length - 1] == ')' || lexem[length - 1] == 'x' ||
        lexem[length - 1] == 'e' || lexem[length - 1] == 'i') {
      ui->label->setText(ui->label->text().append("*"));
    }
  }
  ui->label->setText(ui->label->text().append(button->text()));
}

void MainWindow::variableOutput() {
  QString lexem = ui->label->text();
  int length = lexem.length();
  if (length > 0 && (lexem[length - 1] == 'y' || lexem[length - 1] == 'r' ||
                     lexem[length - 1] == 'l' || lexem[length - 1] == 'h')) {
    allclearLabel();
    length = 0;
    lexem = ui->label->text();
  }
  if (length > 0) {
    if (lexem[length - 1] == ')' || lexem[length - 1] == 'x' ||
        lexem[length - 1] == 'e' || lexem[length - 1] == 'i' ||
        (lexem[length - 1] >= '0' && lexem[length - 1] <= '9')) {
      ui->label->setText(ui->label->text().append("*"));
    } else if (lexem[length - 1] == '.') {
      ui->label->setText(ui->label->text().append("0*"));
    }
  }
  ui->label->setText(ui->label->text().append("x"));
}

void MainWindow::constOutput() {
  QPushButton *button = (QPushButton *)sender();
  QString lexem = ui->label->text();
  int length = lexem.length();
  if (length > 0 && (lexem[length - 1] == 'y' || lexem[length - 1] == 'r' ||
                     lexem[length - 1] == 'l' || lexem[length - 1] == 'h')) {
    allclearLabel();
    length = 0;
    lexem = ui->label->text();
  }
  if (length > 0) {
    if (lexem[length - 1] == ')' || lexem[length - 1] == 'x' ||
        lexem[length - 1] == 'e' || lexem[length - 1] == 'i' ||
        (lexem[length - 1] >= '0' && lexem[length - 1] <= '9')) {
      ui->label->setText(ui->label->text().append("*"));
    } else if (lexem[length - 1] == '.') {
      ui->label->setText(ui->label->text().append("0*"));
    }
  }
  if (button->text() == 'e') {
    ui->label->setText(ui->label->text().append("e"));
  } else {
    ui->label->setText(ui->label->text().append("pi"));
  }
}

void MainWindow::dotOutput() {
  int flag = 0;
  QString lexem = ui->label->text();
  int length = lexem.length();
  if (length > 0 && (lexem[length - 1] == 'y' || lexem[length - 1] == 'r' ||
                     lexem[length - 1] == 'l' || lexem[length - 1] == 'h')) {
    allclearLabel();
    length = 0;
    lexem = ui->label->text();
  }
  for (int i = 0; i < length; i++) {
    if (lexem[i] == '.') {
      flag = 1;
    } else if (lexem[i] < '0' && lexem[i] != '.') {
      flag = 0;
    }
  }
  if (flag == 0) {
    QPushButton *button = (QPushButton *)sender();
    if (length == 0) {
      ui->label->setText(ui->label->text().append("0"));
    } else {
      if (lexem[length - 1] == ')' || lexem[length - 1] == 'x' ||
          lexem[length - 1] == 'e' || lexem[length - 1] == 'i') {
        ui->label->setText(ui->label->text().append("*0"));
      } else if (lexem[length - 1] < '0') {
        ui->label->setText(ui->label->text().append("0"));
      }
    }
    ui->label->setText(ui->label->text().append(button->text()));
  }
}

void MainWindow::allclearLabel() { ui->label->setText(""); }

void MainWindow::operatorsOutput() {
  QPushButton *button = (QPushButton *)sender();
  QString lexem = ui->label->text();
  int length = lexem.length();
  if (length > 0 && (lexem[length - 1] == 'y' || lexem[length - 1] == 'r' ||
                     lexem[length - 1] == 'l' || lexem[length - 1] == 'h')) {
    allclearLabel();
    length = 0;
    lexem = ui->label->text();
  }
  int count = 0;
  for (int i = 0; i < length; i++) {
    if (lexem[i] == ')') {
      count++;
    } else if (lexem[i] == '(') {
      count--;
    }
  }
  if (length == 0) {
    if (button->text() == '+' || button->text() == '-') {
      ui->label->setText(ui->label->text().append(button->text()));
    }
  } else {
    if (lexem[length - 1] == '(') {
      if (button->text() == '-' || button->text() == '+') {
        ui->label->setText(ui->label->text().append(button->text()));
      }
    } else {
      if (lexem[length - 1] != '+' && lexem[length - 1] != '-' &&
          lexem[length - 1] != '*' && lexem[length - 1] != '/' &&
          lexem[length - 1] != '^' && lexem[length - 1] != '%') {
        if (lexem[length - 1] == '.') {
          ui->label->setText(ui->label->text().append("0"));
        }
        if (button->text() == "÷") {
          ui->label->setText(ui->label->text().append("/"));
        } else {
          ui->label->setText(ui->label->text().append(button->text()));
        }
      }
    }
  }
}

void MainWindow::bracketOutput() {
  QPushButton *button = (QPushButton *)sender();
  QString lexem = ui->label->text();
  int length = lexem.length();
  if (length > 0 && (lexem[length - 1] == 'y' || lexem[length - 1] == 'r' ||
                     lexem[length - 1] == 'l' || lexem[length - 1] == 'h')) {
    allclearLabel();
    length = 0;
    lexem = ui->label->text();
  }
  int count = 0;
  for (int i = 0; i < length; i++) {
    if (lexem[i] == ')') {
      count++;
    } else if (lexem[i] == '(') {
      count--;
    }
  }
  if (button->text() == '(') {
    if (length > 0) {
      if (lexem[length - 1] == '.') {
        ui->label->setText(ui->label->text().append("0"));
      }
      if (lexem[length - 1] != '+' && lexem[length - 1] != '-' &&
          lexem[length - 1] != '*' && lexem[length - 1] != '/' &&
          lexem[length - 1] != '^' && lexem[length - 1] != '%' &&
          lexem[length - 1] != '(') {
        ui->label->setText(ui->label->text().append("*"));
      }
    }
    ui->label->setText(ui->label->text().append(button->text()));
  } else {
    if (count < 0) {
      if (lexem[length - 1] == '.') {
        ui->label->setText(ui->label->text().append("0"));
        ui->label->setText(ui->label->text().append(button->text()));
      }
      if ((lexem[length - 1] >= '0' && lexem[length - 1] <= '9') ||
          lexem[length - 1] == 'e' || lexem[length - 1] == 'i' ||
          lexem[length - 1] == ')' || lexem[length - 1] == 'x') {
        ui->label->setText(ui->label->text().append(button->text()));
      }
    }
  }
}

void MainWindow::functionOutput() {
  QPushButton *button = (QPushButton *)sender();
  QString lexem = ui->label->text();
  int length = lexem.length();
  if (length > 0 && (lexem[length - 1] == 'y' || lexem[length - 1] == 'r' ||
                     lexem[length - 1] == 'l' || lexem[length - 1] == 'h')) {
    allclearLabel();
    length = 0;
    lexem = ui->label->text();
  }
  if (length > 0) {
    if (lexem[length - 1] >= '0' || lexem[length - 1] == ')') {
      ui->label->setText(ui->label->text().append("*"));
    }
  }
  if (button->text() == "sin") {
    ui->label->setText(ui->label->text().append(button->text() + "("));
  } else if (button->text() == "cos") {
    ui->label->setText(ui->label->text().append(button->text() + "("));
  } else if (button->text() == "tan") {
    ui->label->setText(ui->label->text().append(button->text() + "("));
  } else if (button->text() == "asin") {
    ui->label->setText(ui->label->text().append(button->text() + "("));
  } else if (button->text() == "acos") {
    ui->label->setText(ui->label->text().append(button->text() + "("));
  } else if (button->text() == "atan") {
    ui->label->setText(ui->label->text().append(button->text() + "("));
  } else if (button->text() == "ln") {
    ui->label->setText(ui->label->text().append(button->text() + "("));
  } else if (button->text() == "log") {
    ui->label->setText(ui->label->text().append(button->text() + "("));
  } else if (button->text() == "√") {
    ui->label->setText(ui->label->text().append("sqrt("));
  }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  if (key >= Qt::Key_0 && key <= Qt::Key_9) {
    this->findChild<QPushButton *>("button_" + event->text())->click();
  } else if (key == Qt::Key_Period) {
    ui->button_dot->click();
  } else if (key == Qt::Key_ParenLeft) {
    ui->button_leftb->click();
  } else if (key == Qt::Key_ParenRight) {
    ui->button_rightb->click();
  } else if (key == Qt::Key_Backspace) {
    ui->button_allclear->click();
  } else if (key == Qt::Key_Plus) {
    ui->button_plus->click();
  } else if (key == Qt::Key_Minus) {
    ui->button_minus->click();
  } else if (key == Qt::Key_Slash) {
    ui->button_div->click();
  } else if (key == Qt::Key_Asterisk) {
    ui->button_mult->click();
  } else if (key == Qt::Key_Percent) {
    ui->button_mod->click();
  } else if (key == Qt::Key_E) {
    ui->button_e->click();
  } else if (key == Qt::Key_P) {
    ui->button_pi->click();
  } else if (key == Qt::Key_X) {
    ui->button_variable->click();
  } else if (key == Qt::Key_Equal) {
    ui->button_eq->click();
  }
}

void MainWindow::equalOutput() {
  QString lexem = ui->label->text();
  int length = lexem.length();
  if (length > 0 && (lexem[length - 1] == 'y' || lexem[length - 1] == 'r' ||
                     lexem[length - 1] == 'l' || lexem[length - 1] == 'h')) {
    allclearLabel();
    length = 0;
    lexem = ui->label->text();
  }
  int count = 0;
  for (int i = 0; i < length; i++) {
    if (lexem[i] == ')') {
      count++;
    } else if (lexem[i] == '(') {
      count--;
    }
  }
  if (lexem.length() == 0 || lexem.length() > 255) {
    ui->label->setText("Invalid expression length");
  } else {
    double d = 1.0;
    if (ui->label->text().contains('x')) {
      bool ok;
      d = QInputDialog::getDouble(this, tr("Variable"), tr("Enter value:"), 1.0,
                                  -1000000.0, 1000000.0, 16, &ok);
    }
    if (count == 0) {
      if (lexem[length - 1] != '+' && lexem[length - 1] != '-' &&
          lexem[length - 1] != '*' && lexem[length - 1] != '/' &&
          lexem[length - 1] != '^' && lexem[length - 1] != '%') {
        char *buf = (char *)calloc(ui->label->text().size(), sizeof(char));
        strncpy(buf, ui->label->text().toLocal8Bit().data(),
                ui->label->text().size());
        double result = 1.0;
        int resultCalc = calculatePN(buf, &result, d);
        free(buf);
        if (resultCalc == OK) {
          QString out = QString::number(result, 'g', 16);
          ui->label_2->setText(ui->label->text().append("="));
          ui->label->setText(out);
        } else if (resultCalc == ERROR) {
          ui->label_2->setText(ui->label->text().append("="));
          ui->label->setText("Error");
        } else if (resultCalc == INFNTY) {
          ui->label_2->setText(ui->label->text().append("="));
          ui->label->setText("Infinity");
        }
      }
    } else {
      ui->label_2->setText(ui->label->text().append("="));
      ui->label->setText(
          "Amount of the opening and closing brackets are not equal");
    }
  }
}

void MainWindow::plotFunction() {
  QString buf = ui->label_2->text();
  wind = new Graph();
  wind->setWindowTitle("Graph");
  if (!buf.isEmpty()) {
    buf.resize(buf.length() - 1);
    wind->buffer = buf;
    if (ui->label_2->text().contains('x')) {
      wind->show();
    } else {
      if (ui->label->text() == "Error" || ui->label->text() == "Infinity" ||
          fabs(ui->label->text().toDouble()) > 1000000) {
        QMessageBox::warning(this, "Warning!", "Result is NaN or Infinity!");
      } else if (ui->label->text() ==
                 "Amount of the opening and closing brackets are not equal") {
        QMessageBox::warning(this, "Warning!", "Invalid syntax!");
      } else {
        wind->show();
      }
    }
  }
}

void MainWindow::creditC() {
  cc = new CreditCalc();
  cc->setWindowTitle("Credit_Calc");
  cc->show();
}
