#include "includes/utils.h"

void validate_args(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "USAGE: project_manager: <WATCH_PATH>\n");
    exit(EXIT_FAILURE);
  }

  if (argv[1] == "create") {
    fprintf(stdout, "DB created\n");
    exit(EXIT_SUCCESS);
  }
}

void check_error(int handler, char *err_message, int exit_code) {
  if (handler == -1) {
    fprintf(stderr, "%s\n", err_message);
    exit(exit_code);
  }
}
