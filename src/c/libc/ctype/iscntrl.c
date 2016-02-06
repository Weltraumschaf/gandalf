
int iscntrl(int ch) {
    return (unsigned)ch < 0x20 || ch == 0x7f;
}
