#include "../drivers/screen.h"

/*
 * The kernels entry point.
 */
void main() {
//  clear_screen();
//  print_char('G', 0, 0, WHITE_ON_BLACK);
	char* video_memory = (char *) get_screen_offset(79, 24);
  *video_memory = 'X';
  
  for (;;) {
    // wait...
  }
}
