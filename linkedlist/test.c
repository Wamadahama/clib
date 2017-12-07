#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int foo[10] = {1,2,3,4,5,6,7,8,9};
  //foo[3] == *(foo + 3);;
  printf("%d == %d\n", foo[3], *(foo + 3));

  char * bar = "bazz";
  //bar[3] != *(bar + 3;)
  printf("%c == %c\n", bar[3], *(bar + 3));
}
