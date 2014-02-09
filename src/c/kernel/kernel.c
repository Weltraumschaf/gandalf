
#include "low_level.h"
#include "../drivers/screen.h"

/*
 * The kernels entry point.
 */
void main() {
//    clear_screen();
//  print_char('G', 0, 0, WHITE_ON_BLACK);
  	char* video_memory = (char *) get_screen_offset(0, 15);
    *video_memory = 'X';
  
    update_cursor(3, 3);
    
  for (;;) {
    sleep(1000);
  }
}
