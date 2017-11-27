#include <stdio.h>
#include <stdlib.h>

void processArguments(int argc, char** argv, char* path) {
  if (argc > 2) {
    printf("%s\n", "Numar prea mare de argumente!");
    exit(0);
  }
  if (argc == 2) {
    path = realpath(argv[1], path);
  } else {
    path = realpath(argv[0], path);
  }
  if (path == NULL) {
    printf("%s\n", "Cale inexistenta");
    exit(0);
  }
}

int main(int argc, char** argv) {

  char *path;

  processArguments(argc, argv, path);

  // printf("%s\n", path);

  free(path);
}
