#include "main.h"
#include "kernel.h"
#include "gandalf.h"
#include "tty.h"
#include "../util/util.h"
/*
 * The kernels entry point.
 */
void main() {
    kernel_boot();
    tty_initialize();
    gandalf_prepareScreen();
    gandalf_showBootScreen();
    sleep(10000);

    tty_clear();
    gandalf_showWelcomeScreen();
    sleep(10000);

    tty_clear();
    tty_setCursor(0, 0);
    tty_setEnableCursor(true);
    tty_setAutoScrolling(true);
    welcome();
    show_flags();
    // run();
}
