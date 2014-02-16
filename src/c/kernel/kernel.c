#include "kernel.h"
#include <stdbool.h>
#include "tty.h"
#include "../util/util.h"
#include "../libc/include/string.h"
#include "../libc/include/stdio.h"

#define TIMER_START 10

void welcome() {
    tty_setColor(DEFAULT_COLOR_INVERTED);
    println("  Gandalf 1.0                                                                   ");
    tty_setColor(DEFAULT_COLOR);
}

int timer = TIMER_START;

bool timerNotGoneOff() {
    --timer;

    if (0 == timer) {
        timer = TIMER_START;
        return false;
    }

    return true;
}

void assignCpuToSuitableProcess() {
    println("Assign process CPU to suitable process ...");
}

void executeProcess() {
    static bool a = true;

    if (a) {
        a = false;
        println("Execute a ...");
    } else {
        a = true;
        println("Execute b ...");
    }

    sleep(1000);
}

void selectNextSuitableProcess() {
    print("Select next suitable process ...");
}

void run() {
    for (;;) {
        while (timerNotGoneOff()) {
            assignCpuToSuitableProcess();
            executeProcess();
        }

        selectNextSuitableProcess();
    }
}

/*
 * The kernels entry point.
 */
void main() {
    tty_initialize();
    tty_setAutoScrolling(true);
    welcome();
    run();
}
