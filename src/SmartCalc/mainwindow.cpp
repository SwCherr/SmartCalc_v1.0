#include "mainwindow.h"

#include <qcustomplot.h>

#include <QString>
#include <iostream>

#include "../Model/model.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "ui_mainwindow.h"

bool flag_equals{false};
bool is_dot{false};
bool is_first_digit{true};
bool is_first_zero{false};
bool is_operation{false};
int is_left_bracket = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(trig_digits()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(trig_digits()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(trig_digits()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(trig_digits()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(trig_digits()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(trig_digits()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(trig_digits()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(trig_digits()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(trig_digits()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(trig_digits()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(trig_digits()));

  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(trig_operat()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(trig_operat()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(trig_operat()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(trig_operat()));
  connect(ui->pushButton_X_Y, SIGNAL(clicked()), this, SLOT(trig_operat()));
  connect(ui->pushButton_sign, SIGNAL(clicked()), this, SLOT(trig_operat()));
  connect(ui->pushButton_perc, SIGNAL(clicked()), this, SLOT(trig_operat()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(trig_operat()));

  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this,
          SLOT(trig_bracket()));
  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this,
          SLOT(trig_bracket()));

  // SIN, COS, TAN, ASIN, ACOS, ATAN, SQRT, LN, LOG
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trig_trigonom()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trig_trigonom()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trig_trigonom()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trig_trigonom()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trig_trigonom()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trig_trigonom()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(trig_trigonom()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(trig_trigonom()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trig_trigonom()));

  connect(ui->pushButton_equals, SIGNAL(clicked()), this, SLOT(trig_equals()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this,
          SLOT(on_pushButton_AC_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::init_flags_digit() {
  is_dot = false;
  is_first_digit = true;
  is_first_zero = false;
}

void MainWindow::trig_digits() {
  QPushButton *button = (QPushButton *)sender();
  is_operation = false;
  if (flag_equals) {
    flag_equals = false;
    on_pushButton_AC_clicked();
  }

  if (button->text() != "0") {
    if (is_first_zero && !is_dot) {
      QString new_label = ui->label_calc->text();
      new_label.chop(1);
      ui->label_calc->setText(new_label);
      ui->label_calc->setText(ui->label_calc->text().append(button->text()));
      is_first_zero = false;
    } else {
      ui->label_calc->setText(ui->label_calc->text().append(button->text()));
      is_first_digit = false;
    }
    // ОБРАБОТКА НУЛЯ
  } else if (button->text() == "0") {
    if (is_first_digit) {
      ui->label_calc->setText(ui->label_calc->text().append(button->text()));
      is_first_digit = false;
      is_first_zero = true;
    } else {
      if (is_first_zero && is_dot)
        ui->label_calc->setText(ui->label_calc->text().append(button->text()));
      if (!is_first_zero)
        ui->label_calc->setText(ui->label_calc->text().append(button->text()));
    }
  }
}

// ОБРАБОТКА ТОЧКИ
void MainWindow::on_pushButton_comma_clicked() {
  if (is_dot == false) {
    ui->label_calc->setText(ui->label_calc->text().append("."));
    is_dot = true;
  }
}

// ОБРАБОТКА ОПЕРАЦИЙ
void MainWindow::trig_operat() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  double all_numbers = 0.0;
  init_flags_digit();
  if (flag_equals) flag_equals = false;

  if (is_operation) {
    QString new_label = ui->label_calc->text();
    new_label.chop(1);
    ui->label_calc->setText(new_label);
  }

  if (button->text() == "+/-") {
    all_numbers = (ui->label_calc->text()).toDouble();
    all_numbers = all_numbers * -1;
    new_label = QString::number(all_numbers, 'g', 15);
    ui->label_calc->setText(new_label);
  } else if (button->text() == "%") {
    all_numbers = (ui->label_calc->text()).toDouble();
    all_numbers = all_numbers * 0.01;
    new_label = QString::number(all_numbers, 'g', 15);
    ui->label_calc->setText(new_label);
  } else {
    is_operation = true;
    if (button->text() == "X ^ Y") {
      ui->label_calc->setText(ui->label_calc->text().append("^"));
    } else if (button->text() == "MOD") {
      ui->label_calc->setText(ui->label_calc->text().append("M"));
    } else {
      ui->label_calc->setText(ui->label_calc->text().append(button->text()));
    }
  }
}

void MainWindow::trig_bracket() {
  QPushButton *button = (QPushButton *)sender();
  if (flag_equals) {
    flag_equals = false;
    on_pushButton_AC_clicked();
  }

  if (button->text() == "(") {
    ui->label_calc->setText(ui->label_calc->text().append(button->text()));
    is_left_bracket++;
  } else if (button->text() == ")") {
    if (is_left_bracket) {
      ui->label_calc->setText(ui->label_calc->text().append(button->text()));
      is_left_bracket--;
    }
  }
}

void MainWindow::trig_trigonom() {
  QPushButton *button = (QPushButton *)sender();
  if (flag_equals) {
    flag_equals = false;
    on_pushButton_AC_clicked();
  }

  init_flags_digit();
  is_left_bracket++;
  ui->label_calc->setText(ui->label_calc->text().append(button->text()));
  ui->label_calc->setText(ui->label_calc->text().append("("));
}

int MainWindow::check_label() {
  QString str = ui->label_calc->text();
  return str != "" && !is_operation && !is_left_bracket && str != "nan" &&
         str != "-nan" && str != "inf" && str != "-inf";
}

// ОБРАБОТКА РАВНО
void MainWindow::trig_equals() {
  QString str = ui->label_calc->text();
  if (check_label()) {
    QByteArray ba_1 = str.toLocal8Bit();
    char *c_str = ba_1.data();
    int is_error = 0;
    double result = 0.0;
    double value_x = ui->lineEdit_x_value->text().toDouble();

    is_error = start_calculation(c_str, value_x, &result);

    // преобразуем результат в строку и выводим на лэйбл
    if (is_error != 0) {
      on_pushButton_AC_clicked();
    } else if (is_error == 0) {
      QString str_of_res;
      str_of_res = QString::number(result, 'g', 15);
      ui->label_calc->setText(str_of_res);
    }

    init_flags_digit();
    flag_equals = true;
  }
}

// ОБРАБОТКА AC
void MainWindow::on_pushButton_AC_clicked() {
  ui->label_calc->clear();
  flag_equals = false;
  is_dot = false;
  is_first_digit = true;
  is_first_zero = false;
  is_operation = false;
  is_left_bracket = 0;
}

// Обработка ----- ПОСТРОЕНИЕ ГРАФИКОВ -----
void MainWindow::on_pushButton_plotting_clicked() {
  QString str = ui->label_calc->text();
  if (check_label()) {
    QByteArray ba_1 = str.toLocal8Bit();
    char *c_str = ba_1.data();

    // ------ GRAPH ------
    QVector<double> x, y;  // Массивы координат точек
    double max_scale_x, max_scale_y;
    double h_step, X;
    int N;

    // задаем краевые значения
    max_scale_x = ui->spinBox_max_x->value();
    max_scale_y = ui->spinBox_max_y->value();
    h_step = ui->doubleSpinBox_step->value();

    // устанавливаем значения по умолчанию
    if (max_scale_x == 0) max_scale_x = 15;
    if (max_scale_y == 0) max_scale_y = 15;
    if (h_step == 0) h_step = 0.01;

    // калькуляция результата
    double y_result = 0.0;
    X = -max_scale_x;
    N = (max_scale_x * 2) / h_step + 2;

    for (int i = 0; i < N; i++) {
      start_calculation(c_str, X, &y_result);
      x.push_back(X);
      y.push_back(y_result);
      X += h_step;
    }

    ui->GraphPL->xAxis->setRange(-max_scale_x, max_scale_x);
    ui->GraphPL->yAxis->setRange(-max_scale_y, max_scale_y);
    ui->GraphPL->clearGraphs();
    ui->GraphPL->addGraph();
    ui->GraphPL->graph(0)->addData(x, y);
    ui->GraphPL->replot();

    init_flags_digit();
  }
}

void MainWindow::on_pushButton_Credit_clicked() {
  Creditwindow credit_window;
  credit_window.setModal(true);
  credit_window.exec();
}

void MainWindow::on_pushButton_Deposit_clicked() {
  DepositWindow deposit_window;
  deposit_window.setModal(true);
  deposit_window.exec();
}
