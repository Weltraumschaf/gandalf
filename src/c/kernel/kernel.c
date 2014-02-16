#include "kernel.h"
#include <stdbool.h>
#include "tty.h"
#include "../util/util.h"
#include "../libc/include/string.h"
#include "../libc/include/stdio.h"

#define TIMER_START 10

void welcome() {
    println("Gandalf 1.0");
}

//int timer = TIMER_START;
//
//bool timerNotGoneOff() {
//    --timer;
//
//    if (0 == timer) {
//        timer = TIMER_START;
//        return false;
//    }
//
//    return true;
//}
//
//void assignCpuToSuitableProcess() {
//    print("Assign process CPU to suitable process ...\n");
//}
//
//void executeProcess() {
//    static bool a = true;
//
//    if (a) {
//        a = false;
//        print("Execute a ...\n");
//    } else {
//        a = true;
//        print("Execute b ...\n");
//    }
//
//    sleep(1000);
//}
//
//void selectNextSuitableProcess() {
//    print("Select next suitable process ...\n");
//}
//
//void run() {
//    for (;;) {
//        while (timerNotGoneOff()) {
//            assignCpuToSuitableProcess();
//            executeProcess();
//        }
//
//        selectNextSuitableProcess();
//    }
//}

/*
 * The kernels entry point.
 */
void main() {
    tty_initialize();
    welcome();
    //    run();
     println("0000");
     println("1111");
     println("2222");
     println("3333");
     println("4444");
     println("5555");
     println("6666");
     println("7777");
     println("8888");
     print("9999");
}
