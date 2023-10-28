#include "view.h"

#include "ui_view.h"

namespace awfl {
View::View(Controller *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View), controller(c) {
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

  connect(ui->button_variable, SIGNAL(clicked()), this,
          SLOT(variableOrConstOutput()));

  connect(ui->button_e, SIGNAL(clicked()), this, SLOT(variableOrConstOutput()));
  connect(ui->button_pi, SIGNAL(clicked()), this,
          SLOT(variableOrConstOutput()));

  connect(ui->button_allclear, SIGNAL(clicked()), this, SLOT(clearLabel()));

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
}

View::~View() {
  delete ui;
}

void View::clearLabel() { ui->label->setText(""); }

bool View::validLexem(QString &lexem) {
  if (lexem == "Error" || lexem == "Infinity" ||
      lexem == "Amount of the opening and closing brackets are not equal" ||
      lexem == "Invalid expression length") {
    return false;
  }
  return true;
}

bool View::isNotOperator(QChar &c) {
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') {
    return false;
  }
  return true;
}

void View::treatLexemFCV() {
  // Func Const Var
  QString lexem = ui->label->text();
  if (lexem.length() > 0) {
    if (validLexem(lexem) == false) {
      clearLabel();
    } else {
      QChar c = lexem.back();
      if (c == ')' || c == 'x' || c == 'e' || c == 'i' || c.isDigit()) {
        ui->label->setText(ui->label->text().append("*"));
      } else if (c == '.') {
        ui->label->setText(ui->label->text().append("0*"));
      }
    }
  }
}

void View::digitsOutput() {
  QPushButton *button = (QPushButton *)sender();
  QString lexem = ui->label->text();
  if (lexem.length() > 0) {
    if (validLexem(lexem) == false) {
      clearLabel();
    } else {
      QChar c = lexem.back();
      if (c == ')' || c == 'x' || c == 'e' || c == 'i') {
        ui->label->setText(ui->label->text().append("*"));
      }
    }
  }
  ui->label->setText(ui->label->text().append(button->text()));
}

void View::variableOrConstOutput() {
  QPushButton *button = (QPushButton *)sender();
  treatLexemFCV();
  if (button->text() == 'e') {
    ui->label->setText(ui->label->text().append("e"));
  } else if (button->text() == 'x') {
    ui->label->setText(ui->label->text().append(button->text()));
  } else {
    ui->label->setText(ui->label->text().append("pi"));
  }
}

void View::functionOutput() {
  QPushButton *button = (QPushButton *)sender();
  treatLexemFCV();
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

void View::operatorsOutput() {
  QPushButton *button = (QPushButton *)sender();
  QString lexem = ui->label->text();
  if (lexem.length() > 0) {
    if (validLexem(lexem) == false) {
      clearLabel();
    } else {
      QChar c = lexem.back();
      if (c == '(') {
        if (button->text() == '+' || button->text() == '-') {
          ui->label->setText(ui->label->text().append(button->text()));
        }
      } else if (isNotOperator(c) == true) {
        if (c == '.') {
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
  if (lexem.length() == 0) {
    if (button->text() == '+' || button->text() == '-') {
      ui->label->setText(ui->label->text().append(button->text()));
    }
  }
}

void View::dotOutput() {
  QPushButton *button = (QPushButton *)sender();
  QString lexem = ui->label->text();
  if (lexem.length() > 0) {
    if (validLexem(lexem) == false) {
      clearLabel();
    } else {
      bool flag = true;
      for (auto &elem : lexem) {
        if (elem == '.') {
          flag = false;
        } else if (isNotOperator(elem) == false) {
          flag = true;
        }
      }

      QChar c = lexem.back();
      if (c == ')' || c == 'x' || c == 'e' || c == 'i') {
        ui->label->setText(ui->label->text().append("*0."));
      } else if (isNotOperator(c) == false || c == '(') {
        ui->label->setText(ui->label->text().append("0."));
      } else if (c.isDigit() && flag == true) {
        ui->label->setText(ui->label->text().append(button->text()));
      }
    }
  }

  if (lexem.length() == 0) {
    ui->label->setText(ui->label->text().append("0."));
  }
}

void View::bracketOutput() {
  QPushButton *button = (QPushButton *)sender();
  QString lexem = ui->label->text();
  if (lexem.length() > 0) {
    if (validLexem(lexem) == false) {
      clearLabel();
    } else {
      QChar c = lexem.back();
      int countOpenB = lexem.count('(');
      int countCloseB = lexem.count(')');
      if (button->text() == '(') {
        if (c == '.') {
          ui->label->setText(ui->label->text().append("0*"));
        } else if (isNotOperator(c) == true && c != '(') {
          ui->label->setText(ui->label->text().append("*"));
        }
        ui->label->setText(ui->label->text().append(button->text()));
      } else {
        if (countOpenB > countCloseB) {
          if (c == '.') {
            ui->label->setText(ui->label->text().append("0)"));
          } else if (c == ')' || c == 'x' || c == 'e' || c == 'i' ||
                     c.isDigit()) {
            ui->label->setText(ui->label->text().append(button->text()));
          }
        }
      }
    }
  }

  if (lexem.length() == 0) {
    if (button->text() == '(') {
      ui->label->setText(ui->label->text().append(button->text()));
    }
  }
}

void View::equalOutput() {
  QString lexem = ui->label->text();
  if (validLexem(lexem) == false) {
    clearLabel();
  }
  if (lexem.length() == 0 || lexem.length() > 255) {
    ui->label->setText("Invalid expression length");
  } else {
    long double x = 0.0;
    if (ui->label->text().contains('x')) {
      bool ok;
      x = QInputDialog::getDouble(this, tr("Variable"), tr("Enter value:"), 1.0,
                                  -1000000.0, 1000000.0, 6, &ok);
    }

    int countOpenB = lexem.count('(');
    int countCloseB = lexem.count(')');

    if (countOpenB == countCloseB) {
      QChar c = lexem.back();
      if (isNotOperator(c) == true) {
        auto calc = controller->calculate(lexem.toStdString(), x);
        if (calc.first == OK) {
          QString out = QString::number(calc.second, 'f', 7);
          ui->label_2->setText(ui->label->text().append("="));
          ui->label->setText(out);
        } else if (calc.first == ERROR) {
          ui->label_2->setText(ui->label->text().append("="));
          ui->label->setText("Error");
        } else if (calc.first == INF) {
          ui->label_2->setText(ui->label->text().append("="));
          ui->label->setText("Infinity");
        }
      }
    } else {
      // while (countOpenB != countCloseB) {
      // ui->label_2->setText(ui->label->text().append(")"));
      //   ++countCloseB;
      // }
      // ui->label_2->setText(ui->label->text().append("="));
      ui->label->setText(
          "Amount of the opening and closing brackets are not equal");
    }
  }
}

void View::plotFunction() {
  QString lexem = ui->label_2->text();
  if (!lexem.isEmpty()) {
    lexem.resize(lexem.length() - 1);
  }
  wind = new Graph(controller, lexem);
  wind->setWindowTitle("Graph");
  wind->setAttribute(Qt::WA_DeleteOnClose);
  wind->show();
}

void View::keyPressEvent(QKeyEvent *event) {
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
    // ui->button_e->click();
    ui->label->setText(ui->label->text().append("e"));
  } else if (key == Qt::Key_P) {
    ui->button_pi->click();
  } else if (key == Qt::Key_X) {
    ui->button_variable->click();
  } else if (key == Qt::Key_Equal) {
    ui->button_eq->click();
  }
}
}  // namespace awfl
