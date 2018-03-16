#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// >128 (the alphabet) 
#define HT_PRIME_1 131 
#define HT_PRIME_2 133

#define HT_INITIAL_BASE_SIZE 50

// Entry in the hashtable
typedef struct {
  char* key;
  char* value; 
} ht_item;

typedef struct {
  int size;
  int count;
  int base_size;
  ht_item** items; 
} hash_table;

static ht_item* ht_new_item(const char*, const char*);
static void ht_del_item(ht_item*);
hash_table* ht_new();
void ht_delete_table(hash_table*);

void ht_insert(hash_table*, const char*, const char*);
char* ht_search(hash_table*, const char*);
void ht_delete(hash_table*, const char*);
