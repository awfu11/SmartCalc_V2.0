#include "creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(cCalc()));
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::cCalc() {
  double loan = ui->doubleSpinBox->value();
  double percent = ui->doubleSpinBox_2->value();
  if (ui->comboBox_4->currentIndex() == 0) {
    percent *= 12.0;
  }
  double month = ui->doubleSpinBox_3->value();
  if (ui->comboBox_5->currentIndex() == 1) {
    month *= 12.0;
  }
  if (ui->comboBox->currentIndex() == 0) {
    double total = 0.0, over = 0.0, payment = 0.0;
    annuityCredit(loan, percent, month, &total, &payment, &over);
    QString strTotal = QString::number(total, 'f', 2);
    QString strPayment = QString::number(payment, 'f', 2);
    QString strOver = QString::number(over, 'f', 2);
    ui->label_6->setText(strPayment);
    ui->label_10->setText(strTotal);
    ui->label_8->setText(strOver);
  } else {
    double total = 0.0, over = 0.0, paymentf = 0.0, paymentl = 0.0;
    diffCredit(loan, percent, month, &total, &paymentf, &paymentl, &over);
    QString strTotal = QString::number(total, 'f', 2);
    QString strPaymentf = QString::number(paymentf, 'f', 2);
    QString strPaymentl = QString::number(paymentl, 'f', 2);
    QString strOver = QString::number(over, 'f', 2);
    ui->label_6->setText("от " + strPaymentl + " до " + strPaymentf);
    ui->label_10->setText(strTotal);
    ui->label_8->setText(strOver);
  }
  QString money;
  if (ui->comboBox_3->currentIndex() == 0) {
    money = " RUB";
  } else if (ui->comboBox_3->currentIndex() == 1) {
    money = " USD";
  } else {
    money = " EUR";
  }
  ui->label_6->setText(ui->label_6->text() + money);
  ui->label_8->setText(ui->label_8->text() + money);
  ui->label_10->setText(ui->label_10->text() + money);
}
