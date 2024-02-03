#ifndef NOTIFY_H
#define NOTIFY_H

#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <stdio.h>
#include <stdlib.h>

void init_libnotify();
void notify(NotifyNotification *handler, char *notification_message);

#endif
