
int isprint(int ch) {
    return (unsigned)ch - 0x20 < 0x5f;
}
