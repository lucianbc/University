#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

// https://stackoverflow.com/questions/70842/execute-program-from-within-a-c-program

void processArguments(int argc, char* argv[], char buff[255], char redirects[3][PATH_MAX]) {
  if (argc == 1) {
    printf("%s\n", "Specificati calea catre fisier");
    exit(0);
  }
  if (argc > 8) {
    printf("%s\n", "Prea multe argumente");
    exit(0);
  }
  strcpy(buff, argv[1]);

  for (int i = 2; i < argc; i+=2) {
    if (argv[i][0] != '-') {
      printf("%s\n", "Format redirect gresit!");
      exit(0);
    }
    int nr = argv[i][1] - '0';
    if (nr < 0 || nr > 2) {
      printf("%s\n", "Identificator fisier gresit. Introduceti un numar intre 0 si 2 inclusiv");
      exit(0);
    }
    strcpy(redirects[nr], argv[i + 1]);
  }
}

int main(int argc, char* argv[]) {
  char path[PATH_MAX];
  char redirects[3][PATH_MAX] = {"", "", ""};
  processArguments(argc, argv, path, redirects);

  pid_t pid = fork();

  if (pid < 0) {
    return errno;
  } else if (pid == 0) {
    if (strcmp(redirects[0], "") != 0) { // 0 -> input
      int fd = open(redirects[0], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
      if (fd < 0) {
        printf("%s\n", "Nu s-a putut deschide fisierul de stdin");
        exit(0);
      }
      dup2(fd, STDIN_FILENO);
    }

    if (strcmp(redirects[1], "") != 0) { // 1 -> output
      int fd = open(redirects[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
      if (fd < 0) {
        printf("%s\n", "Nu s-a putut deschide fisierul de stdout");
        exit(0);
      }
      dup2(fd, STDOUT_FILENO);
    }

    if (strcmp(redirects[2], "") != 0) { // 2 -> error
      int fd = open(redirects[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
      if (fd < 0) {
        printf("%s\n", "Nu s-a putut deschide fisierul de stderr");
        exit(0);
      }
      dup2(fd, STDERR_FILENO);
    }

    char *argv[] = {path, NULL};
    execve(path, argv, NULL);
    perror(NULL);
  } else {
    wait(NULL);
    printf("%s\n", "Done");
  }

  return 0;
}
