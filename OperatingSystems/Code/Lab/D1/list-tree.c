#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

void remove_end_slash(char * path) {
  if (path[strlen(path) - 1] == '/')
    path[strlen(path) - 1] = '\0';
}

void print(char * name, unsigned int level) {
  if (strcmp(name, "..") == 0 || strcmp(name, ".") == 0) return;
  char level_pad[] = "|--";
  int pad_length = level * strlen(level_pad);
  char pad[pad_length];
  for (int i = 0; i < pad_length; i++) {
    pad[i] = level_pad[i % strlen(level_pad)];
  }
  pad[pad_length] = '\0';
  printf("%s%s\n", pad, name);
}

void list_tree(char * path, unsigned int level) {
  // printf("calea: %s\n", path);

  DIR * d = opendir(path);

  if (d == NULL) {
    printf("Directorul nu a putut fi deschis!\n");
    return;
  }

  while(1) {
    struct dirent * entry = readdir(d);
    if (!entry)
      break;
    char * name = entry->d_name;
    print(name, level);

    if (entry->d_type == DT_DIR &&
        strcmp(name, "..") != 0 &&
        strcmp(name, ".") != 0) {
      char new_path[PATH_MAX];
      int new_path_length = snprintf(new_path, PATH_MAX, "%s/%s", path, name);
      if (new_path_length >= PATH_MAX) {
        printf("%s\n", "path too long");
      } else {
        list_tree(new_path, level + 1);
      }
    }
  }
  closedir(d);
}

void list_tree_drive(char * directory) {
  printf("%s\n", directory);
  remove_end_slash(directory);
  list_tree(directory, 1);
}

void processArguments(int argc, char * argv[], char * path) {

  if (argc > 2) {
    printf("%s\n", "Argumente invalide: Numar prea mare de argumente");
    exit(0);
  }

  if (argc == 1) {
    char current_path[PATH_MAX];
    if (getcwd(current_path, sizeof(current_path)) != NULL) {
      strcpy(path, current_path);
      return;
    } else {
      printf("%s\n", "Calea curenta nu a putut fi citita!");
      exit(0);
    }
  }

  if (argc == 2) {
    strcpy(path, argv[1]);
    return;
  }
}

int main(int argc, char *argv[]) {

  char arg[PATH_MAX];

  processArguments(argc, argv, arg);

  list_tree_drive(arg);

  return 0;
}
