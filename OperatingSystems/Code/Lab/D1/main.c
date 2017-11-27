#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int is_folder(const char * path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISDIR(path_stat.st_mode);
}

int main() {

  // int stat = is_folder("./mxxxain.c");

  char fullPath[4096];

  char myPath[] = "./asfsd";

  char *rez = realpath(myPath, fullPath);

  if (rez == NULL) {
    printf("%s\n", "no path");
    return 0;
  }

  printf("%s\n", fullPath);

  return 0;
}
