#ifndef INOTIFY_H
#define INOTIFY_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>

int init_inotify();
int add_dir(int queue, char *dir);

#endif
