#include "model.h"

int push(Node_t** head, char* value, int type_element, int priority) {
  int error = 0;
  Node_t* tmp = malloc(sizeof(Node_t));
  if (tmp == NULL)
    error = STACK_OVERFLOW;
  else {
    memcpy(tmp->value, value, 250);
    tmp->type = type_element;
    tmp->priority = priority;
    tmp->prev = *head;
    *head = tmp;
  }
  return error;
}

Node_t* pop_up_element(Node_t** head) {
  Node_t* out;
  if ((*head) == NULL) {
    out = NULL;
  } else {
    out = *head;
    *head = (*head)->prev;
  }
  return out;
}

void reverse_stack(Node_t* head, Node_t** head_reverse) {
  while (head) {
    push(head_reverse, &head->value[0], head->type, head->priority);
    head = head->prev;
  }
}

void remove_stack(Node_t** stack) {
  Node_t* tmp;
  if (stack) {
    while (*stack != NULL) {
      tmp = (*stack)->prev;
      free(*stack);
      *stack = tmp;
    }
  }
}

// void print_stack(const Node_t* head) {
//   printf("stack > ");
//   while (head) {
//     printf("%s = %d | ", head->value, head->type);
//     head = head->prev;
//   }
//   printf("\n");
// }
