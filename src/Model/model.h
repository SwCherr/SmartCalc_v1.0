#ifndef S21_SMART_CALC_MODEL
#define S21_SMART_CALC_MODEL

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define SIZE 255
enum Type_value {NUMBER, OPERATORS, BRACKET, TRIGONOMETRY, UNARY};
enum Error_value {OK, INCORRECT_EXPRESSION, STACK_OVERFLOW, STACK_UNDERFLOW, OUT_OF_MEMORY};

typedef struct Node_stack {
  char value[250];
  int type;
  int priority;
  struct Node_stack *prev;
} Node_t;

/* ------------ MAIN CALC ------------- */
int start_calculation(char* expression, double x_value, double* result);
int calculation(Node_t* polish, double* result);
double operators_culc(char* char_oper, double prev_num, double next_num);
double trigonometry_culc(char* char_oper, double next_num);
double unary_culc(char* char_oper, double next_num);
int operators_func(Node_t** num_stack, Node_t* polish);
int trigonometry_func(Node_t** num_stack, Node_t* polish);
int unary_func(Node_t** num_stack, Node_t* polish);

/* ------------- CREDIT -------------- */
void credit_calculate(double sum, int term, double rate, int type_pay, double* min_payment, 
                      double* max_payment, double* total_payments, double* overpayment);

/* ------------- DEPOSIT ------------- */
void deposit_calculate(double deposit, int placement_period, double percent_rate, 
                      double tax_rate, int pay_period, int capitalization, 
                      double* percent_sum, double* tax_sum, double* deposit_end_sum);
void iteration_leap_year(int* flag_leap_year, int* days_in_year);
double year_tax(double year_income_sum, int tax_rate);
int first_period(int* Mounth, int pay_period, int index, int days_in_year);
int control_year(int* Mounth, int pay_period, int* index, int* flag_leap_year, 
                 int* days_in_year, int* i_period, int* curr_day_in_year);

/* ------- TO POLISH NOTATION -------- */
void parser_to_polish_notation(char **expression, Node_t** polish, double x_value);
void parser_next_element(char *expression, char *curr_element, int* priority, int* type);
int is_unar_operation(char* curr_el, char* prev_el, int type_prev);
int get_priority(char* curr_element_str);
void converter_to_polish_notation(Node_t* head, Node_t** head_polish_not);
int converter_number(Node_t* h_tmp, Node_t** h_polish);
int converter_operators(Node_t* h_tmp, Node_t** h_polish, Node_t** h_oper);
int converter_trigonometry(Node_t* h_tmp, Node_t** h_oper);
int converter_bracket(Node_t* h_tmp, Node_t** h_polish, Node_t** h_oper);

/* -------------- STACK -------------- */
int push(Node_t **head, char *value, int type_element, int priority);
Node_t* pop_up_element(Node_t** head);
void print_stack(const Node_t* head);
void reverse_stack(Node_t* head, Node_t** head_reverse);
void remove_stack(Node_t** stack);
void delete_up_element(Node_t** head);

#ifdef __cplusplus
}
#endif

#endif  // S21_SMART_CALC_MODEL
