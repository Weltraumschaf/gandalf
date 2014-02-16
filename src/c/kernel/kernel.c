#include <stdbool.h>
#include "tty.h"
#include "../util/util.h"
#include "../libc/include/string.h"
#include "../libc/include/stdio.h"

#define TIMER_START 10

//void welcome() {
//    print("Gandalf 1.0\n");
//}
//
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
//    printf("Hello, kernel World!\n");
//    welcome();
    //    run();
    // print("0000\n");
    // print("1111\n");
    // print("2222\n");
    // print("3333\n");
    // print("4444\n");
    // print("5555\n");
    // print("6666\n");
    // print("7777\n");
    // print("8888\n");
    // print("9999\n");
}
