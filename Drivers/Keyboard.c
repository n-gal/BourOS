#include "Keyboard.h"
#include "Ports.h"
#include "../Cpu/Isr.h"
#include "Screen.h"

static void KeyboardCallback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = PortByteIn(0x60);
    char *sc_ascii;
    IntToAscii(scancode, sc_ascii);
    KPrint("Keyboard scancode: ", GREEN_ON_BLACK);
    KPrint(sc_ascii, GREEN_ON_BLACK);
    KPrint(", ", GREEN_ON_BLACK);
    PrintLetter(scancode);
    KPrint("\n", GREEN_ON_BLACK);
}

void InitKeyboard() {
   RegisterInterruptHandler(IRQ1, KeyboardCallback); 
}

void PrintLetter(u8 scancode) {
    switch (scancode) {
        case 0x0:
            KPrint("ERROR", GREEN_ON_BLACK);
            break;
        case 0x1:
            KPrint("ESC", GREEN_ON_BLACK);
            break;
        case 0x2:
            KPrint("1", GREEN_ON_BLACK);
            break;
        case 0x3:
            KPrint("2", GREEN_ON_BLACK);
            break;
        case 0x4:
            KPrint("3", GREEN_ON_BLACK);
            break;
        case 0x5:
            KPrint("4", GREEN_ON_BLACK);
            break;
        case 0x6:
            KPrint("5", GREEN_ON_BLACK);
            break;
        case 0x7:
            KPrint("6", GREEN_ON_BLACK);
            break;
        case 0x8:
            KPrint("7", GREEN_ON_BLACK);
            break;
        case 0x9:
            KPrint("8", GREEN_ON_BLACK);
            break;
        case 0x0A:
            KPrint("9", GREEN_ON_BLACK);
            break;
        case 0x0B:
            KPrint("0", GREEN_ON_BLACK);
            break;
        case 0x0C:
            KPrint("-", GREEN_ON_BLACK);
            break;
        case 0x0D:
            KPrint("+", GREEN_ON_BLACK);
            break;
        case 0x0E:
            KPrint("Backspace", GREEN_ON_BLACK);
            break;
        case 0x0F:
            KPrint("Tab", GREEN_ON_BLACK);
            break;
        case 0x10:
            KPrint("Q", GREEN_ON_BLACK);
            break;
        case 0x11:
            KPrint("W", GREEN_ON_BLACK);
            break;
        case 0x12:
            KPrint("E", GREEN_ON_BLACK);
            break;
        case 0x13:
            KPrint("R", GREEN_ON_BLACK);
            break;
        case 0x14:
            KPrint("T", GREEN_ON_BLACK);
            break;
        case 0x15:
            KPrint("Y", GREEN_ON_BLACK);
            break;
        case 0x16:
            KPrint("U", GREEN_ON_BLACK);
            break;
        case 0x17:
            KPrint("I", GREEN_ON_BLACK);
            break;
        case 0x18:
            KPrint("O", GREEN_ON_BLACK);
            break;
        case 0x19:
            KPrint("P", GREEN_ON_BLACK);
            break;
		case 0x1A:
			KPrint("[", GREEN_ON_BLACK);
			break;
		case 0x1B:
			KPrint("]", GREEN_ON_BLACK);
			break;
		case 0x1C:
			KPrint("ENTER", GREEN_ON_BLACK);
			break;
		case 0x1D:
			KPrint("LCtrl", GREEN_ON_BLACK);
			break;
		case 0x1E:
			KPrint("A", GREEN_ON_BLACK);
			break;
		case 0x1F:
			KPrint("S", GREEN_ON_BLACK);
			break;
        case 0x20:
            KPrint("D", GREEN_ON_BLACK);
            break;
        case 0x21:
            KPrint("F", GREEN_ON_BLACK);
            break;
        case 0x22:
            KPrint("G", GREEN_ON_BLACK);
            break;
        case 0x23:
            KPrint("H", GREEN_ON_BLACK);
            break;
        case 0x24:
            KPrint("J", GREEN_ON_BLACK);
            break;
        case 0x25:
            KPrint("K", GREEN_ON_BLACK);
            break;
        case 0x26:
            KPrint("L", GREEN_ON_BLACK);
            break;
        case 0x27:
            KPrint(";", GREEN_ON_BLACK);
            break;
        case 0x28:
            KPrint("'", GREEN_ON_BLACK);
            break;
        case 0x29:
            KPrint("`", GREEN_ON_BLACK);
            break;
		case 0x2A:
			KPrint("LShift", GREEN_ON_BLACK);
			break;
		case 0x2B:
			KPrint("\\", GREEN_ON_BLACK);
			break;
		case 0x2C:
			KPrint("Z", GREEN_ON_BLACK);
			break;
		case 0x2D:
			KPrint("X", GREEN_ON_BLACK);
			break;
		case 0x2E:
			KPrint("C", GREEN_ON_BLACK);
			break;
		case 0x2F:
			KPrint("V", GREEN_ON_BLACK);
			break;
        case 0x30:
            KPrint("B", GREEN_ON_BLACK);
            break;
        case 0x31:
            KPrint("N", GREEN_ON_BLACK);
            break;
        case 0x32:
            KPrint("M", GREEN_ON_BLACK);
            break;
        case 0x33:
            KPrint(",", GREEN_ON_BLACK);
            break;
        case 0x34:
            KPrint(".", GREEN_ON_BLACK);
            break;
        case 0x35:
            KPrint("/", GREEN_ON_BLACK);
            break;
        case 0x36:
            KPrint("Rshift", GREEN_ON_BLACK);
            break;
        case 0x37:
            KPrint("Keypad *", GREEN_ON_BLACK);
            break;
        case 0x38:
            KPrint("LAlt", GREEN_ON_BLACK);
            break;
        case 0x39:
            KPrint("Spc", GREEN_ON_BLACK);
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (scancode <= 0x7f) {
                KPrint("Unknown key down", GREEN_ON_BLACK);
            } else if (scancode <= 0x39 + 0x80) {
                KPrint("key up ", GREEN_ON_BLACK);
                PrintLetter(scancode - 0x80);
            } else KPrint("Unknown key up", GREEN_ON_BLACK);
            break;
    }
}