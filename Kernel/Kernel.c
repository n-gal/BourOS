#include "../Drivers/Screen.h"
#include "../Drivers/Keyboard.h"
#include "../Libc/string.h"
#include "../Cpu/Isr.h"
#include "../Cpu/Timer.h"

#define VIDEO_MEMORY 0xb8000
#define WHITE_ON_BLACK 0x0f



void Main() {

    IsrInstall();
    ClearScreen();
    asm volatile("sti");
    InitKeyboard();

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
    KPrint("> ", GREEN_ON_BLACK);

    while(1)
    {

    }

}


void UserInput(char *input) {
    if (StrCmp(input, "END") == 0) {
        KPrint("Stopping the CPU. Bye!\n", GREEN_ON_BLACK);
        asm volatile("hlt");
    }
    KPrint("You said: ", GREEN_ON_BLACK);
    KPrint(input, GREEN_ON_BLACK);
    KPrint("\n> ", GREEN_ON_BLACK);
}