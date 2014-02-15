#include "util.h"

void sleep(int count) {
    int i = count * 100000;

    while (i > 0) {
        --i;
    }
}
