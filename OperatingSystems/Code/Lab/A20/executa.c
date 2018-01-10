#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

// https://stackoverflow.com/questions/70842/execute-program-from-within-a-c-program

void processArguments(int argc, char* argv[], char buff[255]) {
  if (argc == 1) {
    printf("%s\n", "Specificati calea catre fisier");
    exit(0);
  }
  strcpy(buff, argv[1]);
}

int main(int argc, char* argv[]) {

  char path[PATH_MAX];

  processArguments(argc, argv, path);

  pid_t pid = fork();

  if (pid < 0) {
    return errno;
  } else if (pid == 0) {
    char *argv[] = {path, NULL};
    execve(path, argv, NULL);
    perror(NULL);
  } else {
    wait(NULL);
    printf("%s\n", "Done");
  }

  return 0;
}
