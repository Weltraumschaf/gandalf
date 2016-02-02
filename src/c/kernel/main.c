#include "main.h"
#include "kernel.h"

/*
 * The kernels entry point.
 */
void main() {
    //    kernel_boot();
    tty_initialize();
    gandalf_prepareScreen();
    gandalf_showBootScreen();
    sleep(1000);

    tty_clear();
    gandalf_showWelcomeScreen();
    sleep(1000);

    tty_clear();
    tty_setCursor(0, 0);
    tty_setEnableCursor(true);
    tty_setAutoScrolling(true);
    welcome();
    run();
}
