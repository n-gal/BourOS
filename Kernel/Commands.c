#include "CommandParser.h"
#include "Commands.h"
#include "../Libc/String.h"
#include "../Drivers/Screen.h"

void CMHelp(char* command, char* args) {
    if(StrCmp(args, "HELP") == 0) 
        KPrint("Displays command list and explains the purpose of a command\n", targColor);

    else if(StrCmp(args, "CLEAR") == 0)
        KPrint("Clears the screen\n", targColor);

    else if(StrCmp(args, "COLOR") == 0)
        KPrint("Sets the color of the command prompt\n", targColor);

    else
    {
        KPrint("For more information, type HELP followed by the command name\n\n", targColor);
        KPrint("HELP    Sets the color of the command prompt\n", targColor);
        KPrint("CLEAR   Clears the screen\n", targColor);
        KPrint("COLOR   Sets the color of the command prompt\n", targColor);
    }
}

void CMClear(char* command, char* args){
    ClearScreen();
}

void CMColor(char* command, char* args){
    int col = AsciiToInt(args);
    targColor = col;
    SetAllTextColor(targColor);
}