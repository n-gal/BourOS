#include "Isr.h"
#include "Idt.h"
#include "../Drivers/Screen.h"
#include "Ports.h"
#include "../Libc/String.h"

isr_t interruptHandlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */
void IsrInstall() {
    SetIdtGate(0, (u32)isr0);
    SetIdtGate(1, (u32)isr1);
    SetIdtGate(2, (u32)isr2);
    SetIdtGate(3, (u32)isr3);
    SetIdtGate(4, (u32)isr4);
    SetIdtGate(5, (u32)isr5);
    SetIdtGate(6, (u32)isr6);
    SetIdtGate(7, (u32)isr7);
    SetIdtGate(8, (u32)isr8);
    SetIdtGate(9, (u32)isr9);
    SetIdtGate(10, (u32)isr10);
    SetIdtGate(11, (u32)isr11);
    SetIdtGate(12, (u32)isr12);
    SetIdtGate(13, (u32)isr13);
    SetIdtGate(14, (u32)isr14);
    SetIdtGate(15, (u32)isr15);
    SetIdtGate(16, (u32)isr16);
    SetIdtGate(17, (u32)isr17);
    SetIdtGate(18, (u32)isr18);
    SetIdtGate(19, (u32)isr19);
    SetIdtGate(20, (u32)isr20);
    SetIdtGate(21, (u32)isr21);
    SetIdtGate(22, (u32)isr22);
    SetIdtGate(23, (u32)isr23);
    SetIdtGate(24, (u32)isr24);
    SetIdtGate(25, (u32)isr25);
    SetIdtGate(26, (u32)isr26);
    SetIdtGate(27, (u32)isr27);
    SetIdtGate(28, (u32)isr28);
    SetIdtGate(29, (u32)isr29);
    SetIdtGate(30, (u32)isr30);
    SetIdtGate(31, (u32)isr31);

    // Remap the PIC
    PortByteOut(0x20, 0x11);
    PortByteOut(0xA0, 0x11);
    PortByteOut(0x21, 0x20);
    PortByteOut(0xA1, 0x28);
    PortByteOut(0x21, 0x04);
    PortByteOut(0xA1, 0x02);
    PortByteOut(0x21, 0x01);
    PortByteOut(0xA1, 0x01);
    PortByteOut(0x21, 0x0);
    PortByteOut(0xA1, 0x0); 

    // Install the IRQs
    SetIdtGate(32, (u32)irq0);
    SetIdtGate(33, (u32)irq1);
    SetIdtGate(34, (u32)irq2);
    SetIdtGate(35, (u32)irq3);
    SetIdtGate(36, (u32)irq4);
    SetIdtGate(37, (u32)irq5);
    SetIdtGate(38, (u32)irq6);
    SetIdtGate(39, (u32)irq7);
    SetIdtGate(40, (u32)irq8);
    SetIdtGate(41, (u32)irq9);
    SetIdtGate(42, (u32)irq10);
    SetIdtGate(43, (u32)irq11);
    SetIdtGate(44, (u32)irq12);
    SetIdtGate(45, (u32)irq13);
    SetIdtGate(46, (u32)irq14);
    SetIdtGate(47, (u32)irq15);

    SetIdt(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void IsrHandler(registers_t r) {
    KPrint("received interrupt: ", RED_ON_BLACK);
    char s[3];
    IntToAscii(r.int_no, s);
    KPrint(s, RED_ON_BLACK);
    KPrint("\n", RED_ON_BLACK);
    KPrint(exception_messages[r.int_no], RED_ON_BLACK);
    KPrint("\n", RED_ON_BLACK);
}

void RegisterInterruptHandler(u8 n, isr_t handler) {
    interruptHandlers[n] = handler;
}

void IrqHandler(registers_t r) {
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40) PortByteOut(0xA0, 0x20); /* slave */
    PortByteOut(0x20, 0x20); /* master */

    /* Handle the interrupt in a more modular way */
    if (interruptHandlers[r.int_no] != 0) {
        isr_t handler = interruptHandlers[r.int_no];
        handler(r);
    }
}