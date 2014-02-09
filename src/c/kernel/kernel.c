
#include "low_level.h"
#include "../drivers/screen.h"

void welcome() {
//  print_char('G', 0, 0, WHITE_ON_BLACK);
//  	char* video_memory = (char *) get_screen_offset(0, 15);
//    *video_memory = 'X';
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
