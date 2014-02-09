/* Copy bytes from one place to another. */
void memory_copy(char* source, char* dest, int no_bytes) {
  int i;
  
  for (i = 0; i < no_bytes; i++) {
    *(dest + i) = *(source + i); 
  }
}

void sleep(int count) {
  int i = count * 1000;
  
  while (i > 0) {
    --i;
  }
}
