#include "kernel.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "tty.h"
#include "gandalf.h"
#include "../util/util.h"
#include "arch/i386/low_level.h"

void welcome() {
    tty_setColor(DEFAULT_COLOR_INVERTED);
    println("Y  Gandalf 1.0  started :-)                                       "
            "              ");
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

void kernel_boot() {
}

void show_flags() {
    print("Flags:\n");

    print("Interupt: ");

    if (flag_interrupt()) {
        print("enabled\n");
    } else {
        print("disabled\n");
    }

    print("Direction: ");
    if (flag_direction()) {
        print("enabled\n");
    } else {
        print("disabled\n");
    }

    print("Overflow: ");
    if (flag_overflow()) {
        print("enabled\n");
    } else {
        print("disabled\n");
    }

    print("I/O privileged level: ");
    if (flag_io_privileged_level()) {
        print("enabled\n");
    } else {
        print("disabled\n");
    }

    print("Resume: ");
    if (flag_resume()) {
        print("enabled\n");
    } else {
        print("disabled\n");
    }

    print("Virtual mode: ");
    if (flag_virtual_mode()) {
        print("enabled\n");
    } else {
        print("disabled\n");
    }

    print("Alignment check: ");
    if (flag_alignment_check()) {
        print("enabled\n");
    } else {
        print("disabled\n");
    }

    print("Virtual interupt: ");
    if (flag_virtual_interupt()) {
        print("enabled\n");
    } else {
        print("disabled\n");
    }

    print("Virtual interupt pending: ");
    if (flag_virtual_interupt_pending()) {
        print("enabled\n");
    } else {
        print("disabled\n");
    }

    print("Able to use CPUID: ");
    if (flag_able_to_use_cpuid()) {
        print("enabled\n");
    } else {
        print("disabled\n");
    }
}
