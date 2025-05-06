#include "Keyboard.h"
#include "../Cpu/Ports.h"
#include "../Cpu/Isr.h"
#include "Screen.h"
#include "../Libc/String.h"
#include "../Libc/Function.h"
#include "../Kernel/Kernel.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

#define LSHIFTIN 0x2A
#define LSHIFTOUT 0xAA

#define RSHIFTIN 0x36
#define RSHIFTOUT 0xB6

shiftIsDown = 0;

static char keyBuffer[256];
#define SC_MAX 57

const char *scName[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char UPEngScAscii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

const char LOEngScAscii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

const char UPFrScAscii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '°', '+', '?', '?', 'A', 'Z', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '¨', '£', '?', '?', 'Q', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', 'M', '%', 'µ', '?', '\\', 'W', 'X', 'C', 'V', 
        'B', 'N', '?', '.', '/', '§', '?', '?', '?', ' '};

const char LOFrScAscii[] = { '?', '?', '&', 'é', '"', '\'', '(', '-',     
    'è', '_', 'ç', 'à', ')', '=', '?', '?', 'a', 'z', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '^', '$', '?', '?', 'q', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', 'm', 'ù', '*', '?', '\\', 'w', 'x', 'c', 'v', 
        'b', 'n', ',', ';', ':', '!', '?', '?', '?', ' '};

char UPTargScAscii[255];
char LOTargScAscii[255];


static void KeyboardCallback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = PortByteIn(0x60);
    
    if (scancode == LSHIFTIN ||scancode == RSHIFTIN) {
        shiftIsDown = 1;
    } else if (scancode == LSHIFTOUT ||scancode == RSHIFTOUT) {
        shiftIsDown = 0;
    }

    else if (scancode > SC_MAX) return;
    
    else if (scancode == BACKSPACE) {
        int canBackspace = Backspace(keyBuffer);
        if(canBackspace)
            KPrintBackspace();

    } else if (scancode == ENTER) {
        KPrint("\n", targColor);
        UserInput(keyBuffer); /* kernel-controlled function */
        keyBuffer[0] = '\0';

    } else {

        char letter;

        if(shiftIsDown)
            letter = UPTargScAscii[(int)scancode];
        else
            letter = LOTargScAscii[(int)scancode];

        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        Append(keyBuffer, letter);
        KPrint(str, targColor);
    }
    UNUSED(regs);
}

void InitKeyboard() {
   RegisterInterruptHandler(IRQ1, KeyboardCallback); 
   StrCopy(UPTargScAscii, UPEngScAscii);
   StrCopy(LOTargScAscii, LOEngScAscii);
}