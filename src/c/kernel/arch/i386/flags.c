#include "low_level.h"
#include <stdint.h>

// https://en.m.wikipedia.org/wiki/FLAGS_register

#define CARRY_FLAG 0
#define PARITY_FLAG 2
#define ADJUST_FLAG 4
#define ZERO_FLAG 6
#define SIGN_FLAG 7
#define TRAP_FLAG 8
#define INTERUPT_FLAG 9
#define DIRECTION_FLAG 10
#define OVERFLOW_FLAG 11
#define IO_PRIVILEGED_LEVEL_FLAG_LOW 12
#define IO_PRIVILEGED_LEVEL_FLAG_HIGH 13
#define RESUME_FLAG 16
#define VIRTUAL_MODE_FLAG 17
#define ALIGNMENT_CHECK_FLAG 18
#define VIRTUAL_INTERUPT_FLAG 19
#define VIRTUAL_INTERUPT_PENDING_FLAG 20
#define ABLE_TO_USE_CPUID_FLAG 21

uint64_t flags() {
    uint64_t flags;

    __asm__ __volatile__("pushf\n\t"
                         "pop %0"
                         : "=g"(flags) /* output operands */
                         );

    return flags;
}

bool flag_carry() {
    return flags() & (1 << CARRY_FLAG);
}

bool flag_parity() {
    return flags() & (1 << PARITY_FLAG);
}

bool flag_adjust() {
    return flags() & (1 << ADJUST_FLAG);
}

bool flag_zero() {
    return flags() & (1 << ZERO_FLAG);
}

bool flag_sign() {
    return flags() & (1 << SIGN_FLAG);
}

bool flag_trap() {
    return flags() & (1 << TRAP_FLAG);
}

bool flag_interrupt() {
    return flags() & (1 << INTERUPT_FLAG);
}

bool flag_direction() {
    return flags() & (1 << DIRECTION_FLAG);
}

bool flag_overflow() {
    return flags() & (1 << OVERFLOW_FLAG);
}

bool flag_io_privileged_level() {
    uint64_t _flags = flags();

    return (_flags & (1 << IO_PRIVILEGED_LEVEL_FLAG_LOW)) &&
           (_flags & (1 << IO_PRIVILEGED_LEVEL_FLAG_HIGH));
}

bool flag_resume() {
    return flags() & (1 << RESUME_FLAG);
}

bool flag_virtual_mode() {
    return flags() & (1 << VIRTUAL_MODE_FLAG);
}

bool flag_alignment_check() {
    return flags() & (1 << ALIGNMENT_CHECK_FLAG);
}

bool flag_virtual_interupt() {
    return flags() & (1 << VIRTUAL_INTERUPT_FLAG);
}

bool flag_virtual_interupt_pending() {
    return flags() & (1 << VIRTUAL_INTERUPT_PENDING_FLAG);
}

bool flag_able_to_use_cpuid() {
    return flags() & (1 << ABLE_TO_USE_CPUID_FLAG);
}
