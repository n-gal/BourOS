#include "../Drivers/Screen.h"
#include "Util.h"

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
    "|_______/  \\______/  \\______/ |__/       \\______/  \\______/    \n";

    KPrintAt(title, 0, 0);

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