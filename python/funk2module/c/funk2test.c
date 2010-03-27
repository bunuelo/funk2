#include "../../../c/funk2.h"

int main() {
  funk2__start_main_in_separate_thread();
  while(1) {
    usleep(1);
  }
  return 0;
}

