#include "includes/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void validate_args(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "USAGE: project_manager: <PATH> \n");
    exit(EXIT_FAILURE);
  }
}

char *get_base_path(char *path) {

  char *base_path = (char *)malloc(strlen(path) + 1);
  if (base_path == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }

  char *token;
  char *res = strtok_r(path, "/", &token);

  while (res != NULL) {
    base_path = res;
    res = strtok_r(NULL, "/", &token);
  }

  return base_path;
}
