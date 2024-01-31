#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  validate_args(argc, argv);

  exit(EXIT_SUCCESS);
}

void validate_args(int argc, char *argv[]) {

  if (argc < 2) {
    fprintf(stderr, "USAGE: project_manager: <PATH> \n");
    exit(EXIT_FAILURE);
  }
}
