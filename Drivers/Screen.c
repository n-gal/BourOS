#include "Screen.h"
#include "../Cpu/Ports.h"
#include "../Libc/Mem.h"

/* Declaration of private functions */
int GetCursorOffset();
void SetCursorOffset(int offset);
int PrintChar(char c, int col, int row, char attr, int startCol, int lastChar);
int GetOffset(int col, int row);
int GetOffsetRow(int offset);
int GetOffsetCol(int offset);

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Print a message on the specified location
 * If col, row, are negative, we will use the current offset
 */

void KPrintAt(char *message, int col, int row, char attr) {
    /* Set cursor if col/row are negative */
    int startCol = col;
    int offset;
    if (col >= 0 && row >= 0)
        offset = GetOffset(col, row);
    else {
        if(col >= 0) {
            row = GetOffsetRow(GetCursorOffset());
            offset = GetOffset(col, row);
        } else if (row >= 0) {
            col = GetOffsetCol(GetCursorOffset());
            offset = GetOffset(col, row);
        } else{
            offset = GetCursorOffset();
            row = GetOffsetRow(offset);
            col = GetOffsetCol(offset);
        }
    }

    /* Loop through message and print it */
    int i = 0;
    int lastChar = 0;
    while (message[i] != 0) {
        if(message[i + 1] == 0)
            lastChar = 1;
        offset = PrintChar(message[i++], col, row, attr, startCol, lastChar);
        /* Compute row/col for next iteration */
        row = GetOffsetRow(offset);
        col = GetOffsetCol(offset);
    }
}

void KPrint(char *message, char attr) {
    KPrintAt(message, -1, -1, attr);
}

void KPrintBackspace() {
    int offset = GetCursorOffset() - 2;
    int row = GetOffsetRow(offset);
    int col = GetOffsetCol(offset);
    PrintChar(' ', col, row, GREEN_ON_BLACK, col, 1);
    SetCursorOffset(offset);
}


/**********************************************************
 * Private kernel functions                               *
 **********************************************************/


/**
 * Innermost print function for our kernel, directly accesses the video memory 
 *
 * If 'col' and 'row' are negative, we will print at current cursor location
 * If 'attr' is zero it will use 'white on black' as default
 * Returns the offset of the next character
 * Sets the video cursor to the returned offset
 */

int PrintChar(char c, int col, int row, char attr, int startCol, int lastChar) {
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    /* Error control: print a red 'E' if the coords aren't right */
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E'; // Use the first character of the string
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        return GetOffset(col, row);
    }
    
    int offset;
    if (col >= 0 && row >= 0) offset = GetOffset(col, row);
    else offset = GetCursorOffset();

    if (c == '\n') {
        row = GetOffsetRow(offset) + 1; // Move to the next row
        if(startCol >= 0 && lastChar == 0)
            offset = GetOffset(startCol, row);
        else
            offset = GetOffset(0, row); // Move to the first column of the next row
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++) 
            MemoryCopy(GetOffset(0, i) + VIDEO_ADDRESS,
                        GetOffset(0, i-1) + VIDEO_ADDRESS,
                        MAX_COLS * 2);

        /* Blank last line */
        char *last_line = GetOffset(0, MAX_ROWS-1) + VIDEO_ADDRESS;
        for (i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

        offset -= 2 * MAX_COLS;
    }

    SetCursorOffset(offset);
    return offset;
}

int GetCursorOffset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    PortByteOut(REG_SCREEN_CTRL, 14);
    int offset = PortByteIn(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    PortByteOut(REG_SCREEN_CTRL, 15);
    offset += PortByteIn(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void SetCursorOffset(int offset) {
    /* Similar to GetCursorOffset, but instead of reading we write data */
    offset /= 2;
    
    PortByteOut(REG_SCREEN_CTRL, 14);
    PortByteOut(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    PortByteOut(REG_SCREEN_CTRL, 15);
    PortByteOut(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}


void ClearScreen() {
    int screenSize = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = VIDEO_ADDRESS;
    
    for (i = 0; i < screenSize; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    SetCursorOffset(GetOffset(0, 0));
}

int GetOffset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int GetOffsetRow(int offset) { return offset / (2 * MAX_COLS); }
int GetOffsetCol(int offset) { return (offset - (GetOffsetRow(offset)*2*MAX_COLS))/2; }

