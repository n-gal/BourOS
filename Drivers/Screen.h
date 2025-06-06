#ifndef SCREEN_H
#define SCREEN_H

#include "../Cpu/Types.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define GREEN_ON_BLACK 0x02
#define RED_ON_BLACK 0x04
#define RED_ON_WHITE 0xf4

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

extern int targColor; 

/* Public kernel API */
void ClearScreen();
void KPrintAt(char *message, int col, int row, char attr);
void KPrint(char *message, char attr);
void KPrintBackspace();
void SetAllTextColor(u8 attr);

#endif