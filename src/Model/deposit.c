#include "model.h"

void deposit_calculate(double deposit, int placement_period,
                       double percent_rate, double tax_rate, int pay_period,
                       int capitalization, double* percent_sum, double* tax_sum,
                       double* deposit_end_sum) {
  int Mounth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int days_in_year = 365;
  int flag_leap_year = 3;
  int flag_tax = 0;
  int i_period = 0;
  int index = 0;
  double curr_sum = deposit;
  double curr_percent = 0.0;
  double curr_accum_percent_for_tax = 0.0;

  i_period = first_period(Mounth, pay_period, index, days_in_year);
  int curr_day_in_year = i_period;
  int i = placement_period - i_period;

  for (; i >= 0; i -= i_period) {
    curr_percent = (curr_sum * percent_rate * i_period / days_in_year) / 100;
    if (capitalization) curr_sum += curr_percent;
    *percent_sum += curr_percent;
    curr_accum_percent_for_tax += curr_percent;

    flag_tax = control_year(Mounth, pay_period, &index, &flag_leap_year,
                            &days_in_year, &i_period, &curr_day_in_year);
    if (flag_tax) {
      *tax_sum += year_tax(curr_accum_percent_for_tax, tax_rate);
      curr_accum_percent_for_tax = 0.0;
      flag_tax = 0;
    }
  }

  if (i < 0) {
    curr_percent =
        (curr_sum * percent_rate * (i + i_period) / days_in_year) / 100;
    if (capitalization) curr_sum += curr_percent;
    *percent_sum += curr_percent;
    curr_accum_percent_for_tax += curr_percent;
  }

  *tax_sum += year_tax(curr_accum_percent_for_tax, tax_rate);
  *deposit_end_sum = curr_sum;
}

void iteration_leap_year(int* flag_leap_year, int* days_in_year) {
  if (*flag_leap_year == 4) {
    *flag_leap_year = 1;
    *days_in_year = 365;
  } else {
    *flag_leap_year += 1;
    if (*flag_leap_year == 4) *days_in_year = 366;
  }
}

double year_tax(double year_income_sum, int tax_rate) {
  double return_result = 0.0;
  double key_rate = 13;  // ключевая ставка ЦБ
  double non_taxable_income = 1000000 * key_rate / 100;
  double taxable_income = year_income_sum - non_taxable_income;
  if (taxable_income > 0) return_result += taxable_income * tax_rate / 100;
  return return_result;
}

int control_year(int* Mounth, int pay_period, int* index, int* flag_leap_year,
                 int* days_in_year, int* i_period, int* curr_day_in_year) {
  int flag_tax = 0;
  if (pay_period == 30) {
    if (*index == 10)
      flag_tax = 1;
    else if (*index == 11) {
      iteration_leap_year(flag_leap_year, days_in_year);
      *index = 0;
    } else
      *index += 1;
    if (*flag_leap_year == 4 && *index == 1)
      *i_period = 29;
    else
      *i_period = Mounth[*index];
  } else {
    *curr_day_in_year += *i_period;
    if (*curr_day_in_year > 365) {
      if (*flag_leap_year == 4) {
        if (*curr_day_in_year > 366) {
          *curr_day_in_year %= *days_in_year;
          iteration_leap_year(flag_leap_year, days_in_year);
          if (pay_period == 365) *i_period = *days_in_year;
          flag_tax = 1;
        }
      } else {
        *curr_day_in_year %= *days_in_year;
        iteration_leap_year(flag_leap_year, days_in_year);
        if (pay_period == 365) *i_period = *days_in_year;
        flag_tax = 1;
      }
    }
  }
  return flag_tax;
}

int first_period(int* Mounth, int pay_period, int index, int days_in_year) {
  int i_period = 0;
  if (pay_period == 7)
    i_period = pay_period;
  else if (pay_period == 30)
    i_period = Mounth[index];
  else if (pay_period == 365)
    i_period = days_in_year;
  return i_period;
}
