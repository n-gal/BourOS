#include "CommandParser.h"
#include "Commands.h"
#include "../Libc/String.h"
#include "../Drivers/Screen.h"
#include "../Drivers/Keyboard.h"

void CMHelp(char* command, char* args) {
    if(StrCmpCI(args, "HELP") == 0) 
        KPrint("Displays command list and explains the purpose of a command\n", targColor);

    else if(StrCmpCI(args, "CLEAR") == 0)
        KPrint("Clears the screen\n", targColor);

    else if(StrCmpCI(args, "COLOR") == 0)
        KPrint("Sets the color of the command prompt\n", targColor);
    
    else if(StrCmpCI(args, "SETLAYOUT") == 0){
        KPrint("Sets the keyboard layout language, available layouts are:\n", targColor);
        KPrint("ENG     QWERTY layout\n", targColor);
        KPrint("FR      AZERTY layout\n", targColor);
    }
    else
    {
        KPrint("For more information, type HELP followed by the command name\n\n", targColor);
        KPrint("HELP        Sets the color of the command prompt\n", targColor);
        KPrint("CLEAR       Clears the screen\n", targColor);
        KPrint("COLOR       Sets the color of the command prompt\n", targColor);
        KPrint("SETLAYOUT   Sets the keyboard layout language\n", targColor);
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

void CMSetLayout(char* command, char* args){

    if(StrCmpCI(args, "ENG") == 0){
        StrCopy(UPTargScAscii, UPEngScAscii);
        StrCopy(LOTargScAscii, LOEngScAscii);
    }

    else if(StrCmpCI(args, "FR") == 0){
        StrCopy(UPTargScAscii, UPFrScAscii);
        StrCopy(LOTargScAscii, LOFrScAscii);
    }

    else{
        QuotePrint(args,"Is not a recognised keyboard layout, known layouts are:\n", targColor);
        KPrint("ENG     QWERTY layout\n", targColor);
        KPrint("FR      AZERTY layout\n", targColor);
    }

}