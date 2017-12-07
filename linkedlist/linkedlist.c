#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
  int data;
  struct node* next;
  struct node* prev;
} node; 

// Returns the head node, Can take NULL as the next parameter for just an empty node. 
node* create_list(int data, node* next) {
  // Create head node 
  node* new_node = (node*)(malloc(sizeof(node)));

  // If they passed in NULL or a bad node as a paramter then set next to NULL
  // else set the next node 
  if(next != NULL) {
    new_node->next = next; 
  } else {
    new_node->next = NULL;
  }

  // Set the data in the head node
  new_node->data = data;

  // Return the head node
  return new_node;
    
}

// Creates a new node 
node* create_node(int data) {
  node* new = (node*)(malloc(sizeof(node)));
  new->data = data;
  new->next = NULL; 
  new->prev = NULL; 
  return new; 
}

node* append_node(node* head, node* append) {

  if(append == NULL) return NULL; 

  node* trav = head; 

  // Traverse to the end of the list 
  while(trav->next != NULL) {
    trav = trav->next; 
  }

  trav->next = append;
  append->prev = trav; 
  append->next = NULL;

  return head; 
    
}

node* prepend_node(node* head, node* append) {
  if(append == NULL) return NULL;
  append->next = head;
  head = append;
  return append; 
}

// TODO
// insert, delete

// Gets the length of the list. 
int list_length(node* head) {
  int len = 0;
  node* trav = head;
  while(trav->next != NULL) {
    trav = trav->next;
    ++len;
  }
  return len; 
}

void print_list(node* head) {

  node* trav = head;
  printf("Head Node -- Data: %d\n", head->data);
  int cnt = 1;

  while(trav->next != NULL) {
    trav = trav->next;
    printf("Node #%d --  Data: %d\n", cnt, trav->data);
    ++cnt;
  }
  
}


char* serialize_single(node* head) {

  node* trav = head; 

  int length = list_length(head);

  char* serial =  malloc(sizeof(char *));// * (int)log10(length)); 

  int buffer_length = 0;

  // Traverse to the end of the list 
  while(trav != NULL) {
    buffer_length += sprintf(serial+buffer_length, "(%d", trav->data);
    // Move the pointer 
    trav = trav->next; 
  }

  for(; length > 0; --length)
    buffer_length += sprintf(serial+buffer_length, ")");

  return serial;
    
}

// Currently broken 
node* deserialize_single(char* text) {
  int i;
  node* head = create_node(text[1]);
  node* last = head;

  last->data = text[1] - '0'; 

  for(i = 2; i < strlen(text); ++i) {
    char unit = text[i];

    if(unit == '(' || unit == ')' || unit == ' ') {
      continue;
    } else {

      //printf("%d", text[i] - '0');
      // - '0' gets the integer value 
      node* new_node = create_node(text[i] - '0');
      
      new_node->prev = last;
      new_node->next = NULL;
      last->next     = new_node; 
      last = new_node;
    }
  }

  return head;
}

node** deserialize_list(char * text) {
  
}

int main(void) {

  node* head = create_list(0, NULL);

  append_node(head, create_node(1));
  node* append = create_node(2);
  head = append_node(head, append);
  head = append_node(head, create_node(3));
  head = prepend_node(head, create_node(-1));
  // print_list(head);
  char* foo = serialize_single(head);

  puts(foo);

  node* test = deserialize_single("(1 (2 ( 3)))");

  print_list(test);

  return 0; 
}
