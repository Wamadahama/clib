#include <stdio.h>
#include <stdlib.h>

typedef struct queue{
  int data; 
  struct queue* next; 
} queue; 

int queue_len(queue* s) {

  queue* trav = s;
  int n = 1; // Including the head  

  while((trav = trav->next) != NULL) {
    //trav = trav->next;
    ++n; 
  }
  
  return n;
}

int is_empty(queue* s) {
  return queue_len(s) ? 1 : 0;
}

queue* enqueue(queue* head, int data) {
  queue* node = malloc(sizeof*node);
  node->data = data;
  node->next = head;
  return node; 
}

queue* dequeue(queue* s, int * ret) {

  /*
  queue* trav = s;
  queue* prev; 

  while(trav != NULL) {
    prev = trav;
    trav = trav->next;
  }

  printf("%d", prev->data);

  *ret = prev->data;

  return s; 
  */
}

int main(void) {
  queue* q = malloc(sizeof *q);

  q = enqueue(q, 1);
  q = enqueue(q, 5);
  q = enqueue(q, 3);

  printf("%d, %d, %d\n", q->data, q->next->data, q->next->next->data);

  int a, b,c;
  a=b=c =0;

  q = dequeue(q, &a);
  q = dequeue(q, &b);
  q = dequeue(q, &c);
  
  printf("%d %d %d", a,b,c);
}
