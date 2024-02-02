#include "includes/utils.h"

#include <stdio.h>
#include <stdlib.h>

void validate_args(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "USAGE: project_manager: <PATH> \n");
    exit(EXIT_FAILURE);
  }
}

void check_error(int handler, char *err_message, int exit_code) {
  if (handler == -1) {
    fprintf(stderr, "%s\n", err_message);
    exit(exit_code);
  }
}
