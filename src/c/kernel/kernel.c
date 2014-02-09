
#include "low_level.h"
#include "../drivers/screen.h"

void welcome() {
  print("Gandalf 1.0\n");
}

void run() {
  for (;;) {
    sleep(1000);
  }  
}

/*
 * The kernels entry point.
 */
void main() {
  clear_screen();
  welcome();
  run();
}
