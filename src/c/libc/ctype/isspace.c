
int isspace(int ch) {
    return ch == ' ' || (unsigned)ch - '\t' < 5;
}
