#include "depositwindow.h"

#include "../Model/model.h"
#include "ui_depositwindow.h"

DepositWindow::DepositWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::DepositWindow) {
  ui->setupUi(this);
}

DepositWindow::~DepositWindow() { delete ui; }

void DepositWindow::on_pushButton_clicked() {
  double deposit_sum = 0;          // сумма вклада
  int placement_period = 0;        // срок размещения
  double percent_rate = 0;         // процентная ставка
  double tax_rate = 0;             // налоговая ставка
  int frequency_payments = 0;      // периодичность выплат
  int percent_capitalization = 0;  // капитализация процентов
  // ВЫВОД
  double percent_charges = 0;  // начисленные проценты
  double tax_amount = 0;       // сумма налога
  double amount_deposit_end = 0;  // сумма на вкладе к концу срока

  deposit_sum = ui->deposit_sum_2->text().toDouble();
  percent_rate = ui->percent_rate_2->text().toDouble();
  tax_rate = ui->tax_rate_2->text().toDouble();

  // определяем наличие капитализации
  if (ui->percent_capitalization->isChecked()) percent_capitalization = 1;

  // переводим период ВКЛАДА в дни
  int Mounth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (ui->year->isChecked()) {
    int years = ui->placement_period_2->text().toInt();
    int count_leap = 0;
    if (years > 1) count_leap = (years - 1) / 4 + 1;
    placement_period = years * 365 + count_leap;
  } else if (ui->mounth->isChecked()) {
    int index = 0;
    for (int i = 0; i < ui->placement_period_2->text().toInt(); i++) {
      placement_period += Mounth[index++];
      if (index == 12) index = 0;
    }
  } else if (ui->days->isChecked()) {
    placement_period = ui->placement_period_2->text().toInt();
  }

  // переводим период ВЫПЛАТ в дни
  if (ui->in_year->isChecked()) {
    frequency_payments = 365;
  } else if (ui->in_mounth->isChecked()) {
    frequency_payments = 30;
  } else if (ui->in_weeks->isChecked()) {
    frequency_payments = 7;
  }

  if (deposit_sum > 0 && placement_period > 0 && percent_rate > 0 &&
      tax_rate > 0 && frequency_payments > 0) {
    deposit_calculate(deposit_sum, placement_period, percent_rate, tax_rate,
                      frequency_payments, percent_capitalization,
                      &percent_charges, &tax_amount, &amount_deposit_end);

    ui->percent_charges_2->setText(QString::number(percent_charges, 'f', 2));
    ui->tax_amount_2->setText(QString::number(tax_amount, 'f', 2));
    ui->amount_deposit_end_2->setText(
        QString::number(amount_deposit_end, 'f', 2));
  }
}
