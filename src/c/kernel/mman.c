#include <sys/mman.h>

void *mmap (void *__addr, size_t __len, int __prot, int __flags, int __fd, off_t __offset) {
    return NULL;
}

int munmap (void *__addr, size_t __len) __THROW {
    return 0;
}

int mprotect (void *__addr, size_t __len, int __prot) __THROW {
    return 0;
}

int msync (void *__addr, size_t __len, int __flags) __THROW {
    return 0;
}

void *mremap (void *__addr, size_t __old_len, size_t __new_len, unsigned long __may_move) __THROW {
    return NULL;
}

int mincore (void *__start, size_t __len, unsigned char *__vec) {
    return 0;
}

