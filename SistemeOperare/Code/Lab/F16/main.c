#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define justLines 4
#define justWords 2
#define justChars 1

char shouldClose = 0;

typedef struct {
  int lines;
  int words;
  int chars;
} Counts;

int handleOptions(char* opts) {
  // codeaza lwc in biti
  // l -> 4, w -> 2, c-> 1, lw -> 6, wc -> 3, lc-> 5, lwc -> 7
  int code = 0;
  if (strlen(opts) == 0 || opts[0] != '-') {
    printf("%s\n", "Sirul nu respecta formatul necesar pentru optiuni");
    exit(0);
  }

  for (int i = 1; i < strlen(opts); i++) {
    switch (opts[i]) {
      case 'l':
        code = code | justLines;
        break;
      case 'w':
        code = code | justWords;
        break;
      case 'c':
        code = code | justChars;
        break;
      default:
        printf("%s\n", "Optiune nerecunoscuta");
        exit(0);
    }
  }
  return code;
}

FILE* openFile(char* fileName) {
  shouldClose = 1;

  FILE* file = fopen(fileName, "r");

  if (file == NULL) {
    printf("%s\n", "Fisierul nu a putut fi deschis!");
    exit(0);
  }
  return file;
}

void freeResources(FILE* file) {
  if (shouldClose) {
    fclose(file);
  }
}

FILE* processArguments(int argc, char *argv[], int *options) {
  if (argc > 3) {
    printf("%s\n", "Numar prea mare de argumente");
    exit(0);
  }

  if (argc == 1) {
    return stdin;
  }

  if (argc == 2) {
    if (argv[1][0] == '-') {
      *options = handleOptions(argv[1]);
      return stdin;
    }
    else return openFile(argv[1]);
  }

  if (argc == 3) {
    *options = handleOptions(argv[1]);
    return openFile(argv[2]);
  }
}

Counts count(FILE* file) {
  char ch;
  Counts fileCount = { 0, 0, 0};
  while ((ch = getc(file)) != EOF) {
    ++fileCount.chars;
    if (isspace(ch)) ++fileCount.words;
    if (ch == '\n') ++fileCount.lines;
  }
  return fileCount;
}

void output(const Counts * counts, const int options) {
  if (options & justLines) printf("l: %d ", counts->lines);
  if (options & justWords) printf("w: %d ", counts->words);
  if (options & justChars) printf("c: %d ", counts->chars);
  printf("\n");
}

int main(int argc, char *argv[]) {

  int options;

  FILE* input = processArguments(argc, argv, &options);

  Counts counts = count(input);

  output(&counts, options);

  freeResources(input);

  return 0;
}
