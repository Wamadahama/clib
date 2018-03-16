#include "hash.h"

int main(void) {
  hash_table* ht = ht_new();
  ht_insert(ht, "A", "forth");
  ht_insert(ht, "B", "Wax");

  char* a = ht_search(ht, "A");
  char* b = ht_search(ht, "B");

  printf("%s%s", b,a);
  ht_delete_table(ht);
  return 0;
}
