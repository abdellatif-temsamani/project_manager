#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

void validate_args(int argc, char *argv[]);
void check_error(int handler, char *err_message, int exit_code);

#endif
