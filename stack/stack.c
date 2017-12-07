#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
  int data; 
  struct stack* next; 
} stack; 

int stack_len(stack* s) {

  stack* trav = s;
  int n = 1; // Including the head  

  while((trav = trav->next) != NULL) {
    //trav = trav->next;
    ++n; 
  }
  
  return n;
}

void stack_push(stack* s, int data) {
  stack* node = malloc(sizeof *s);
  node->data = data;

  stack* tmp = s->next;
  s->next = node;
  node->next = tmp; 
}

stack* stack_pop(stack* s, int* r) {
  *r = s->data;
  stack* tmp = s;
  s = s->next;
  free(tmp);
  return s; 
}

int main(void) {

  stack* s = malloc(sizeof *s);
  s->next = NULL; 
  s->data = 1;

  stack_push(s, 3);
  stack_push(s, 2);

  int a,b,c;
  a=b=c=0;
  s = stack_pop(s, &a);
  s = stack_pop(s, &b);
  s = stack_pop(s, &c);

  printf("%d %d %d\n", a,b, c);
 
}
