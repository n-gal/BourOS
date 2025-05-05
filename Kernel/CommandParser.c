#include "CommandParser.h"
#include "Commands.h"
#include "../Libc/String.h"
#include "../Drivers/Screen.h"

void ParseCommand(char* command, char* args){
    if(StrLen(command) <= 0)
        return;

    else if(StrCmp(command, "HELP") == 0)
        CMHelp(command, args);
    
    else if(StrCmp(command, "CLEAR") == 0)
        CMClear(command, args);

    else if(StrCmp(command, "COLOR") == 0)
        CMColor(command, args);

    else{
        char incorrectMsg[255] = "'";
        StrCat(incorrectMsg, command, 255);
        StrCat(incorrectMsg, "' ", 255);
        StrCat(incorrectMsg, INVALID_COMMAND, 255);
        KPrint(incorrectMsg, targColor);
    }
}