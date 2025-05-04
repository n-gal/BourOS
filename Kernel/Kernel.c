#include "../Drivers/Screen.h"
#include "Util.h"
#include "../Cpu/Isr.h"
#include "../Cpu/Idt.h"

#define VIDEO_MEMORY 0xb8000
#define WHITE_ON_BLACK 0x0f



void Main() {

    ClearScreen();

    const char* title =
    "/$$$$$$$                                 /$$$$$$   /$$$$$$     \n"
    "| $$__  $$                               /$$__  $$ /$$__  $$   \n"
    "| $$  \\ $$  /$$$$$$  /$$   /$$  /$$$$$$ | $$  \\ $$| $$  \\__/   \n"
    "| $$$$$$$  /$$__  $$| $$  | $$ /$$__  $$| $$  | $$|  $$$$$$    \n"
    "| $$__  $$| $$  \\ $$| $$  | $$| $$  \\__/| $$  | $$ \\____  $$   \n"
    "| $$  \\ $$| $$  | $$| $$  | $$| $$      | $$  | $$ /$$  \\ $$   \n"
    "| $$$$$$$/|  $$$$$$/|  $$$$$$/| $$      |  $$$$$$/|  $$$$$$/   \n"
    "|_______/  \\______/  \\______/ |__/       \\______/  \\______/    \n\n";

    KPrintAt(title, 10, 0, GREEN_ON_BLACK);
    KPrintAt("Ver     1.0\n", 10, -1, GREEN_ON_BLACK);

    IsrInstall();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");


    /*
    int i = 0;
    for (i = 0; i < 24; i++) {
        char str[255];
        IntToAscii(i, str);
        KPrintAt(str, 0, i);
    }

    KPrintAt("This text forces the kernel to scroll. Row 0 will disappear. \n", 0, 24);
    KPrint("And with this text, the kernel will scroll again, and row 1 will disappear too!");
    */

    while(1)
    {

    }

}