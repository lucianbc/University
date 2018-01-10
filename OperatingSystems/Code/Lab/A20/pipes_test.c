#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

  int file_in = open("input.txt", _IOS_APPEND | _IOS_TRUNC);

  if (file_in < 0) return 1;

  if (dup2(file_in, 0) < 0) return 1;

  // char buff[255];
  // scanf("%254s", buff);
  // printf("Hello, %s\n", buff);

  pid_t pid = fork();

  char path[] = "/home/lucian/Documents/University/OperatingSystems/Code/Lab/A20/greet";

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
