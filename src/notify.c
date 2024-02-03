#include "includes/notify.h"
#include "includes/utils.h"

void init_libnotify() {
  int libnotify_status = -1;
  libnotify_status = notify_init("Project Manager");
  check_error(libnotify_status, "Error: creating libinotify", EXIT_FAILURE);
}

void notify(NotifyNotification *handler, char *notification_message) {

  handler =
      notify_notification_new(NULL, notification_message, "dialog-information");
  if (handler == NULL) {
    fprintf(stderr, "Error: Error sending notification\n");
    exit(EXIT_FAILURE);
  }

  notify_notification_show(handler, NULL);
  free(notification_message);
}
