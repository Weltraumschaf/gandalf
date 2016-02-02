#pragma once

#include <stdbool.h>

#define TIMER_START 10

void welcome() ;

bool timerNotGoneOff();

void assignCpuToSuitableProcess();

void executeProcess();

void selectNextSuitableProcess();

void run();

void kernel_boot();
