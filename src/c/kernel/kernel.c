#include "../drivers/screen.h"

/*
 * The kernels entry point.
 */
void main() {
  clear_screen();
//  print_char('G', 0, 0, WHITE_ON_BLACK);
	char* video_memory = (char *) VIDEO_ADDRESS;
  *video_memory = 'G';
  video_memory = (char *) VIDEO_ADDRESS + 0x02;
  *video_memory = 'a';
  video_memory = (char *) VIDEO_ADDRESS + 0x04;
  *video_memory = 'n';
  video_memory = (char *) VIDEO_ADDRESS + 0x06;
  *video_memory = 'd';
  video_memory = (char *) VIDEO_ADDRESS + 0x08;
  *video_memory = 'a';
  video_memory = (char *) VIDEO_ADDRESS + 0x0a;
  *video_memory = 'l';
  video_memory = (char *) VIDEO_ADDRESS + 0x0c;
  *video_memory = 'f';
    
  for (;;) {
    // wait...
  }
}
