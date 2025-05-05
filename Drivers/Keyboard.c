#include "Keyboard.h"
#include "../Cpu/Ports.h"
#include "../Cpu/Isr.h"
#include "Screen.h"
#include "../Libc/String.h"
#include "../Libc/Function.h"
#include "../Kernel/Kernel.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char keyBuffer[256];

#define SC_MAX 57
const char *scName[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char scAscii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void KeyboardCallback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = PortByteIn(0x60);
    
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        int canBackspace = Backspace(keyBuffer);
        if(canBackspace)
            KPrintBackspace();
    } else if (scancode == ENTER) {
        KPrint("\n", targColor);
        UserInput(keyBuffer); /* kernel-controlled function */
        keyBuffer[0] = '\0';
    } else {
        char letter = scAscii[(int)scancode];
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        Append(keyBuffer, letter);
        KPrint(str, targColor);
    }
    UNUSED(regs);
}

void InitKeyboard() {
   RegisterInterruptHandler(IRQ1, KeyboardCallback); 
}