#include "CommandParser.h"
#include "Commands.h"
#include "../Libc/String.h"
#include "../Drivers/Screen.h"

void ParseCommand(char* command, char* args){
    if(StrLen(command) <= 0)
        return;
    else if(StrCmpCI(command, "HELP") == 0)
        CMHelp(command, args);
    else if(StrCmpCI(command, "CLEAR") == 0)
        CMClear(command, args);
    else if(StrCmpCI(command, "COLOR") == 0)
        CMColor(command, args);
    else if(StrCmpCI(command, "SETLAYOUT") == 0)
        CMSetLayout(command, args);
    else
        QuotePrint(command, INVALID_COMMAND, targColor);
}

void QuotePrint(const char* quote, const char* msg, int color){
    char quoteMsg[255] = "'";
    StrCat(quoteMsg, quote, 255);
    StrCat(quoteMsg, "' ", 255);
    StrCat(quoteMsg, msg, 255);
    KPrint(quoteMsg, color);
}