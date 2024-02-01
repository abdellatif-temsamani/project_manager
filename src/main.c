#include "includes/main.h"
#include "includes/utils.h"

#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>

int inotify_queue = -1;
int inotify_status = -1;

void signal_handler(int signal) {
  int close_status = -1;
  fprintf(stdout, "Closing the daemon, bye\n");
  close_status = inotify_rm_watch(inotify_queue, inotify_status);

  if (close_status == -1) {
    fprintf(stderr, "Error: error removing watch queue\n");
    exit(EXIT_FAILURE);
  }

  close(inotify_queue);
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  validate_args(argc, argv);

  char *base_path = get_base_path(argv[1]);
  if (base_path == NULL) {
    fprintf(stderr, "Error: directory not found\n");
    exit(EXIT_FILEPATHERR);
  }

  NotifyNotification *libnotify_handle;
  bool libnotify_status = notify_init("Project Manager");
  if (!libnotify_status) {
    fprintf(stderr, "Error: creating libinotify\n");
    exit(EXIT_FAILURE);
  }

  inotify_queue = inotify_init();
  if (inotify_queue == -1) {
    fprintf(stderr, "Error: creating inotify instance\n");
    exit(EXIT_FAILURE);
  }

  uint32_t mask = IN_CREATE | IN_DELETE | IN_ONLYDIR;
  inotify_status = inotify_add_watch(inotify_queue, argv[1], mask);
  if (inotify_status == -1) {
    fprintf(stderr, "Error: could not watch over %s\n", argv[1]);
    exit(EXIT_FILEPATHERR);
  }

  char buffer[4096];
  const struct inotify_event *watch_event;

  int read_length = -1;
  char *libnotify_message = NULL;
  printf("waiting for events....\n");

  signal(SIGABRT, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  while (true) {
    read_length = read(inotify_queue, buffer, sizeof(buffer));
    if (read_length == -1) {
      fprintf(stderr, "Error: Error reading from inotify instance\n");
      exit(EXIT_FAILURE);
    }

    for (char *ptr = buffer; ptr < buffer + read_length;
         ptr += sizeof(struct inotify_event) + watch_event->len) {

      libnotify_message = NULL;
      watch_event = (const struct inotify_event *)ptr;

      if (watch_event->mask & IN_ISDIR) {
        if (watch_event->mask & IN_CREATE) {
          // notification_message = "project created";

          libnotify_message = (char *)malloc(32 * sizeof(char));
          sprintf(libnotify_message, "project %s created", watch_event->name);
        } else if (watch_event->mask & IN_DELETE) {
          // notification_message = "project deleted";
          libnotify_message = (char *)malloc(32 * sizeof(char));
          sprintf(libnotify_message, "project %s deleted", watch_event->name);
        }
      }

      if (libnotify_message == NULL) {
        continue;
      }

      libnotify_handle = notify_notification_new(
          NULL, libnotify_message, "dialog-information");
      if (libnotify_handle == NULL) {
        fprintf(stderr, "Error: Error sending notification\n");
        exit(EXIT_FAILURE);
      }

      notify_notification_show(libnotify_handle, NULL);
      free(libnotify_message);
    }
  }
}
