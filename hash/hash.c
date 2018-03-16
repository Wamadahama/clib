#include "hash.h"
#include "prime.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL}; // Deleted sentinel 

// hashing function
static unsigned int hash(const char* s, const int a, const int bucket_count) {

  long hash = 0;
  int len = strlen(s);

  for(int i = 0; i < len; ++i) {
    hash += (long)pow(a, len - (i+1)) * s[i];
  }

  hash = hash % bucket_count;
  return (int)hash;
}

// Implement double hashing
static int ht_get_hash(const char* s, const int num_buckets, const int attempt) {
  int hash_a = hash(s, HT_PRIME_1, num_buckets);
  int hash_b = hash(s, HT_PRIME_2, num_buckets);
  return (hash_a + (attempt * (hash_b + 1)));
}
 
// Initializes an item 
static ht_item* ht_new_item(const char* key, const char* value) {
  ht_item* i = malloc(sizeof(ht_item)); // allocate memory for the item 
  // Copy input characters into item 
  i->key   = strdup(key);
  i->value = strdup(value);
  return i; 
}

// Deletes a item 
static void ht_del_item(ht_item* i) {
  free(i->key);
  free(i->value);
  free(i);
}

hash_table* ht_new_sized(const int base_size) {
  hash_table* ht = malloc(sizeof(hash_table));
  ht->base_size = base_size;

  ht->size = next_prime(ht->base_size);
  ht->count = 0;

  ht->items = calloc((size_t)ht->size, sizeof(ht_item*));

  return ht;
  
}

// Initialize a new hash table 
hash_table* ht_new() {
  // Make space for the hash table 
  /*
  hash_table* new = malloc(sizeof(hash_table));
  new->size  = 53; // arbitrary
  new->count = 0;
  new->items = calloc((size_t)new->size, sizeof(ht_item*));
  return new;
  */
  ht_new_sized(HT_INITIAL_BASE_SIZE);
}


static void ht_resize(hash_table* ht, const int base_size) {
  if(base_size < HT_INITIAL_BASE_SIZE) {
    return; 
  }

  hash_table* new_ht = ht_new_sized(base_size);
  for(int i = 0; i < ht->size; i++) {
    ht_item* item = ht->items[i];
    if(item != NULL && item != &HT_DELETED_ITEM) {
      ht_insert(new_ht, item->key, item->value);
    }
  }

  ht->base_size = new_ht->base_size;
  ht->count = new_ht->count;

  int tmp_size = ht->size;
  ht->size = new_ht->size;
  new_ht->size = tmp_size;

  ht_item** tmp_items = ht->items;
  ht->items = new_ht->items;
  new_ht->items = tmp_items;

  ht_delete_table(new_ht);
  
}

static void ht_resize_up(hash_table* ht) {
  int new_size = ht->base_size * 2;
  ht_resize(ht, new_size);
}

static void ht_resize_down(hash_table* ht) {
  int new_size = ht->base_size / 2;
  ht_resize(ht, new_size);
}

// Frees a hash table 
void ht_delete_table(hash_table* ht) {
  // For each item in the hashtable
  for(int i = 0; i < ht->size; ++i) {
    // Get item
    ht_item* it = ht->items[i];
    if(it != NULL) // if the space isn't null then pass it to the delete item 
      ht_del_item(it);
  }
  // free the items array and the hash table 
  free(ht->items);
  free(ht);
}

void ht_insert(hash_table* ht, const char* key, const char* value) {

  // Check to see if we need to resize 
  int load = ht->count * 100 / ht->size;
  if (load > 70) {
    ht_resize_up(ht);
  }

  // Get index 
  ht_item* item = ht_new_item(key, value);
  int index = ht_get_hash(item->key, ht->size, 0);

  ht_item* cur_item = ht->items[index];
  int i = 1;

  // If there is a collision then do it again until a value is found 
  while(cur_item != NULL) {

    // support update 
    if(cur_item != &HT_DELETED_ITEM) {
      if(strcmp(cur_item->key, key) == 0) {
	ht_del_item(cur_item);
	ht->items[index] = item;
	return;
      }
    }

    // there is a collision so move along
    index = ht_get_hash(item->key, ht->size, i);
    cur_item = ht->items[index];
    i++;
  }

  ht->items[index] = item;
  ht->count++;
}

char* ht_search(hash_table* ht, const char* key) {

  int index = ht_get_hash(key, ht->size, 0);
  ht_item* item = ht->items[index];
  int i = 1;

  while(item != NULL) {

    if(item != &HT_DELETED_ITEM) {
      if(strcmp(item->key, key) == 0)
	return item->value;
    }

    index = ht_get_hash(key, ht->size, i);
    item = ht->items[index];
    ++i;
  }

  return NULL;
}


void ht_delete(hash_table* ht, const char* key) {

  int load = ht->count * 100 / ht->size;
  if(load < 10) {
    ht_resize_down(ht);
  }
  
  int index = ht_get_hash(key, ht->size, 0);
  ht_item* item = ht->items[index];
  int i = 1;
  while(item != NULL) {

    if(item != &HT_DELETED_ITEM) {
      if(strcmp(item->key, key) == 0) {
	ht_del_item(item);
	ht->items[index] = &HT_DELETED_ITEM;
      }
    }

    index = ht_get_hash(key, ht->size, i);
    item  = ht->items[index];
    i++;
  }
  ht->count--;
}
