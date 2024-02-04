#ifndef MAIN_H
#define MAIN_H

#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>

#define EXIT_FILEPATHERR 2

void signal_handler(int signal);

#endif
