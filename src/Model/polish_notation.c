#include "model.h"

void parser_to_polish_notation(char** expression, Node_t** polish,
                               double x_value) {
  Node_t* h_express = NULL;
  Node_t* h_reverse = NULL;
  Node_t* h_to_polish = NULL;
  int type_prev = OPERATORS;
  char prev_el[50] = {0};

  while (strlen(*expression) != 0) {
    int type = 0;
    int priority = 0;
    char curr_el[50] = {0};

    parser_next_element(*expression, curr_el, &priority, &type);
    if (curr_el[0] == 'x') {
      char curr_el_x[50] = {0};
      snprintf(curr_el_x, 50, "%g", x_value);
      push(&h_express, curr_el_x, type, priority);
    } else if (is_unar_operation(curr_el, prev_el, type_prev)) {
      type = UNARY;
      push(&h_express, curr_el, type, priority);
    } else
      push(&h_express, curr_el, type, priority);
    *expression += strlen(curr_el);
    type_prev = type;
    strcpy(prev_el, curr_el);
  }

  reverse_stack(h_express, &h_reverse);
  converter_to_polish_notation(h_reverse, &h_to_polish);
  reverse_stack(h_to_polish, polish);
  remove_stack(&h_express);
  remove_stack(&h_reverse);
  remove_stack(&h_to_polish);
}

int is_unar_operation(char* curr_el, char* prev_el, int type_prev) {
  return ((curr_el[0] == '-' || curr_el[0] == '+') && type_prev != NUMBER &&
          prev_el[0] != ')');
}

void parser_next_element(char* expression, char* curr_el, int* priority,
                         int* type) {
  int index = 0;
  if (isdigit(*expression)) {
    *type = NUMBER;
    while (isdigit(*expression) || *expression == '.') {
      curr_el[index++] = *expression;
      expression++;
    }
  } else if (isalpha(*expression)) {
    if (*expression == 'x') {
      *type = NUMBER;
      curr_el[index++] = *expression;
      expression++;
    } else if (*expression == 'M') {
      *type = OPERATORS;
      curr_el[index++] = '%';
      expression++;
    } else {
      *type = TRIGONOMETRY;
      while (isalpha(*expression)) {
        curr_el[index++] = *expression;
        expression++;
      }
    }
  } else {
    if (*expression == '(' || *expression == ')')
      *type = BRACKET;
    else
      *type = OPERATORS;
    curr_el[index++] = *expression;
  }
  curr_el[index] = '\0';
  *priority = get_priority(curr_el);
}

int get_priority(char* element) {
  int priority = 0;
  if (element[0] == '+')
    priority = 2;
  else if (element[0] == '-')
    priority = 2;
  else if (element[0] == '*')
    priority = 3;
  else if (element[0] == '/')
    priority = 3;
  else if (element[0] == '%')
    priority = 3;  // MOD
  else if (element[0] == '(')
    priority = 1;
  else if (element[0] == ')')
    priority = 6;
  else if (element[0] == '^')
    priority = 4;
  else if (isalpha(*element))
    priority = 4;  // для префиксных операций
  return priority;
}

void converter_to_polish_notation(Node_t* h_src, Node_t** h_polish) {
  Node_t* h_oper = NULL;
  int flag_next_head = 0;
  while (h_src) {
    switch (h_src->type) {
      case NUMBER:
        flag_next_head = converter_number(h_src, h_polish);
        break;
      case OPERATORS:
        flag_next_head = converter_operators(h_src, h_polish, &h_oper);
        break;
      case UNARY:
        flag_next_head = converter_operators(h_src, h_polish, &h_oper);
        break;
      case TRIGONOMETRY:
        flag_next_head = converter_trigonometry(h_src, &h_oper);
        break;
      case BRACKET:
        flag_next_head = converter_bracket(h_src, h_polish, &h_oper);
        break;
    }
    if (flag_next_head) h_src = h_src->prev;
  }

  while (h_oper != NULL) {
    Node_t* up_tmp = h_oper->prev;
    push(h_polish, h_oper->value, h_oper->type, h_oper->priority);
    free(h_oper);
    h_oper = up_tmp;
  }
  remove_stack(&h_oper);
}

int converter_number(Node_t* h_src, Node_t** h_polish) {
  push(h_polish, h_src->value, h_src->type, h_src->priority);
  return 1;
}

int converter_operators(Node_t* h_src, Node_t** h_polish, Node_t** h_oper) {
  int flag_next_head = 0;
  if ((*h_oper) == NULL || (*h_oper)->priority < h_src->priority) {
    flag_next_head = 1;
    push(h_oper, h_src->value, h_src->type, h_src->priority);
  } else if ((*h_oper)->priority >= h_src->priority) {
    flag_next_head = 0;
    while ((*h_oper) != NULL && (*h_oper)->priority >= h_src->priority) {
      Node_t* up_tmp = NULL;
      up_tmp = pop_up_element(h_oper);
      push(h_polish, up_tmp->value, up_tmp->type, up_tmp->priority);
      free(up_tmp);
    }
  }
  return flag_next_head;
}

int converter_trigonometry(Node_t* h_src, Node_t** h_oper) {
  push(h_oper, h_src->value, h_src->type, h_src->priority);
  return 1;
}

int converter_bracket(Node_t* h_src, Node_t** h_polish, Node_t** h_oper) {
  if (h_src->value[0] == '(') {
    push(h_oper, h_src->value, h_src->type, h_src->priority);
  } else if ((h_src)->value[0] == ')') {
    while ((*h_oper) != NULL && (*h_oper)->priority != 1) {
      Node_t* head_up = pop_up_element(h_oper);
      push(h_polish, head_up->value, head_up->type, head_up->priority);
      free(head_up);
    }
    if (*h_oper) {
      Node_t* up_tmp = pop_up_element(h_oper);
      free(up_tmp);
    }
  }
  return 1;
}