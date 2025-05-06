#ifndef  KEYBOARD_H
#define KEYBOARD_H

#include "../Cpu/Types.h"

extern int shiftIsDown;

extern const char UPEngScAscii[];
extern const char LOEngScAscii[];
extern const char UPFrScAscii[];
extern const char LOFrScAscii[];

extern char UPTargScAscii[];
extern char LOTargScAscii[];

void InitKeyboard();

#endif