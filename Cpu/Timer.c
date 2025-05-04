#include "Timer.h"
#include "Isr.h"
#include "../Libc/Function.h"

u32 tick = 0;

static void TimerCallback(registers_t regs) {
    tick++;
    UNUSED(regs);
}

void InitTimer(u32 freq) {
    /* Install the function we just wrote */
    RegisterInterruptHandler(IRQ0, TimerCallback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);
    /* Send the command */
    PortByteOut(0x43, 0x36); /* Command port */
    PortByteOut(0x40, low);
    PortByteOut(0x40, high);
}