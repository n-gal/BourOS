#ifndef UTIL_H
#define UTIL_H

#include "../Cpu/Types.h"

void MemoryCopy(char *source, char *dest, int nbytes);
void MemorySet(u8 *dest, u8 val, u32 len);
void IntToAscii(int n, char str[]);

#endif