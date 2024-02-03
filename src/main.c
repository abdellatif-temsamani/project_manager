#include "includes/main.h"
#include "includes/inotify.h"
#include "includes/notify.h"
#include "includes/utils.h"

int inotify_queue = -1;
int inotify_status = -1;

int main(int argc, char *argv[]) {
  validate_args(argc, argv);

  NotifyNotification *libnotify_handle;
  init_libnotify();

  inotify_queue = init_inotify();
  inotify_status = add_dir(inotify_queue, argv[1]);

  char buffer[4096];
  const struct inotify_event *watch_event;

  signal(SIGABRT, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  int read_length = -1;
  char *libnotify_message = NULL;
  printf("waiting for events....\n");
  while (1) {
    read_length = read(inotify_queue, buffer, sizeof(buffer));
    check_error(read_length, "Error: Error reading from inotify instance",
                EXIT_FAILURE);

    for (char *ptr = buffer; ptr < buffer + read_length;
         ptr += sizeof(struct inotify_event) + watch_event->len) {

      libnotify_message = NULL;
      watch_event = (const struct inotify_event *)ptr;

      if (watch_event->mask & IN_ISDIR) {
        if (watch_event->mask & IN_CREATE) {
          libnotify_message = (char *)malloc(32 * sizeof(char));
          sprintf(libnotify_message, "%s created", watch_event->name);
        } else if (watch_event->mask & IN_DELETE) {
          // notification_message = "project deleted";
          libnotify_message = (char *)malloc(32 * sizeof(char));
          sprintf(libnotify_message, "%s deleted", watch_event->name);
        }
      }

      if (libnotify_message == NULL) {
        continue;
      }

      notify(libnotify_handle, libnotify_message);
    }
  }
}

void signal_handler(int signal) {
  int close_status = -1;
  fprintf(stdout, "Closing the daemon, bye\n");
  close_status = inotify_rm_watch(inotify_queue, inotify_status);

  check_error(close_status, "Error: error removing watch queue", EXIT_FAILURE);

  close(inotify_queue);
  exit(EXIT_SUCCESS);
}
