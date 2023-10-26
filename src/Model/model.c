#include "model.h"

int start_calculation(char* expression, double x_value, double* result) {
  int error = OK;
  Node_t* polish = NULL;
  parser_to_polish_notation(&expression, &polish, x_value);
  error = calculation(polish, result);
  remove_stack(&polish);
  return error;
}

int calculation(Node_t* polish, double* result) {
  int error = OK;
  Node_t* num_stack = NULL;
  double curr_res = 0.0;
  while (polish && !error) {
    if (polish->type == NUMBER) {
      push(&num_stack, polish->value, polish->type, polish->priority);
    } else if (polish->type == OPERATORS) {
      error = operators_func(&num_stack, polish);
    } else if (polish->type == TRIGONOMETRY) {
      error = trigonometry_func(&num_stack, polish);
    } else if (polish->type == UNARY) {
      error = unary_func(&num_stack, polish);
    }
    polish = polish->prev;
  }

  if (!polish && !error) {
    Node_t* tmp = pop_up_element(&num_stack);
    curr_res = atof(tmp->value);
    remove_stack(&tmp);
  }
  *result = curr_res;
  remove_stack(&num_stack);
  return error;
}

int operators_func(Node_t** num_stack, Node_t* polish) {
  int error = OK;
  double curr_res = 0.0;
  double next_num = 0.0;
  double prev_num = 0.0;
  char str_curr_rec[50] = {0};
  if (num_stack) {
    Node_t* next_el = pop_up_element(num_stack);
    Node_t* prev_el = NULL;
    if (num_stack && next_el) {
      prev_el = pop_up_element(num_stack);
      if (prev_el) {
        next_num = atof(next_el->value);
        prev_num = atof(prev_el->value);
        curr_res = operators_culc(&polish->value[0], prev_num, next_num);
        snprintf(str_curr_rec, 50, "%.7lf", curr_res);
        push(num_stack, str_curr_rec, NUMBER, 0);
      } else
        error = STACK_UNDERFLOW;
      if (prev_el) free(prev_el);
    } else
      error = STACK_UNDERFLOW;
    if (next_el) free(next_el);
  } else
    error = STACK_UNDERFLOW;
  return error;
}

int trigonometry_func(Node_t** num_stack, Node_t* polish) {
  int error = OK;
  double curr_res = 0.0;
  double next_num = 0.0;
  char str_curr_rec[50] = {0};
  Node_t* number = pop_up_element(num_stack);
  if (number) {
    next_num = atof(number->value);
    curr_res = trigonometry_culc(&polish->value[0], next_num);
    snprintf(str_curr_rec, 49, "%.7lf", curr_res);
    push(num_stack, str_curr_rec, NUMBER, 0);
  } else
    error = STACK_UNDERFLOW;
  if (number) free(number);
  return error;
}

int unary_func(Node_t** num_stack, Node_t* polish) {
  int error = OK;
  double curr_res = 0.0;
  double next_num = 0.0;
  char str_curr_rec[50] = {0};
  Node_t* number = pop_up_element(num_stack);
  if (number) {
    next_num = atof(number->value);
    curr_res = unary_culc(&polish->value[0], next_num);
    snprintf(str_curr_rec, 49, "%.7lf", curr_res);
    push(num_stack, str_curr_rec, NUMBER, 0);
  } else
    error = STACK_UNDERFLOW;
  if (number) free(number);
  return error;
}

double operators_culc(char* char_oper, double prev_num, double next_num) {
  double curr_res = 0;
  if (*char_oper == '+') {
    curr_res = prev_num + next_num;
  } else if (*char_oper == '-') {
    curr_res = prev_num - next_num;
  } else if (*char_oper == '/') {
    curr_res = prev_num / next_num;
  } else if (*char_oper == '*') {
    curr_res = prev_num * next_num;
  } else if (*char_oper == '^') {
    curr_res = pow(prev_num, next_num);
  } else if (*char_oper == '%') {  // mod
    curr_res = (int)prev_num % (int)next_num;
  }
  return curr_res;
}

double trigonometry_culc(char* char_oper, double next_num) {
  double curr_res = 0;
  if (*char_oper == 's') {
    if (*(char_oper + 1) == 'i') curr_res = sin(next_num);
    if (*(char_oper + 1) == 'q') curr_res = sqrt(next_num);
  } else if (*char_oper == 'c')
    curr_res = cos(next_num);
  else if (*char_oper == 't')
    curr_res = tan(next_num);
  else if (*char_oper == 'a') {
    if (*(char_oper + 1) == 's')
      curr_res = asin(next_num);
    else if (*(char_oper + 1) == 'c')
      curr_res = acos(next_num);
    else if (*(char_oper + 1) == 't')
      curr_res = atan(next_num);
  } else if (*char_oper == 'l') {
    if (*(char_oper + 1) == 'n')
      curr_res = log(next_num);
    else if (*(char_oper + 1) == 'o')
      curr_res = log10(next_num);
  }
  return curr_res;
}

double unary_culc(char* char_oper, double next_num) {
  double curr_res = 0;
  if (*char_oper == '-')
    curr_res = -next_num;
  else if (*char_oper == '+')
    curr_res = next_num;
  return curr_res;
}