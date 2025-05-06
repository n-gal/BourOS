#include "CommandParser.h"
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

    KPrintAt(title, 10, 0, targColor);
    KPrintAt("Ver     1.0\n", 10, -1, targColor);
    KPrint("> ", targColor);
    while(1)
    {

    }

}


void UserInput(char *input) {
    char cmd[256];
    char args[256];
    CommandSeparate(input, cmd, args);
    ParseCommand(cmd, args);
    KPrint("> ", targColor);
}