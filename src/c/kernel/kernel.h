#pragma once

#include <sys/cdefs.h>
#include <stdbool.h>

__BEGIN_DECLS

#define TIMER_START 10

void welcome();

bool timerNotGoneOff();

void assignCpuToSuitableProcess();

void executeProcess();

void selectNextSuitableProcess();

void run();

void kernel_boot();

void show_flags();

__END_DECLS
