
int isxdigit(int ch) {
    return isdigit(ch) || ((unsigned)ch | 32) - 'a' < 6;
}
