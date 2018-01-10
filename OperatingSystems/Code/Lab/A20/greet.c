#include <stdio.h>

int main() {
  char name[255];
  scanf("%254s", name);
  printf("Hello, %s!\n", name);
}
