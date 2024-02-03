#include "includes/inotify.h"
#include "includes/main.h"
#include "includes/utils.h"

int init_inotify() {
  int queue = inotify_init();
  check_error(queue, "Error: creating inotify instance", EXIT_FAILURE);

  return queue;
}

int add_dir(int queue, char *dir) {

  uint32_t mask = IN_CREATE | IN_DELETE | IN_ONLYDIR;
  int inotify_status = inotify_add_watch(queue, dir, mask);
  check_error(inotify_status, "Error: watching over directory",
              EXIT_FILEPATHERR);

  return inotify_status;
}
