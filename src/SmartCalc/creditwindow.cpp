#include "creditwindow.h"

#include <stdlib.h>

#include <QString>

#include "../Model/model.h"
#include "ui_creditwindow.h"

Creditwindow::Creditwindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::Creditwindow) {
  ui->setupUi(this);
}

Creditwindow::~Creditwindow() { delete ui; }

void Creditwindow::on_calculate_clicked() {
  double credit_sum = 0;
  int credit_term = 0;
  double credit_rate = 0;
  int repayment_procedure = 0;

  double min_payment = 0;
  double max_payment = 0;
  double total_payments = 0;
  double overpayment = 0;

  credit_sum = ui->credit_sum_2->text().toDouble();
  credit_rate = ui->credit_rate_2->text().toDouble();

  // определяем тип кредита
  if (ui->annuity->isChecked()) {
    repayment_procedure = 0;
  } else if (ui->differentiated->isChecked()) {
    repayment_procedure = 1;
  }

  // перевод года в месяцы
  if (ui->year->isChecked()) {
    credit_term = ui->credit_term_2->text().toInt() * 12;
  } else if (ui->mounth->isChecked()) {
    credit_term = ui->credit_term_2->text().toInt();
  }

  if (credit_sum > 0 && credit_term > 0 && credit_rate > 0) {
    if ((ui->annuity->isChecked() || ui->differentiated->isChecked())) {
      credit_calculate(credit_sum, credit_term, credit_rate,
                       repayment_procedure, &min_payment, &max_payment,
                       &total_payments, &overpayment);
      ui->max_payment_2->setText(QString::number(max_payment, 'f', 2));
      ui->min_payment_2->setText(QString::number(min_payment, 'f', 2));
      ui->total_payments_2->setText(QString::number(total_payments, 'f', 2));
      ui->overpayment_2->setText(QString::number(overpayment, 'f', 2));
    }
  }
}
