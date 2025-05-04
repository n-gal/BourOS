#ifndef MEM_H
#define MEM_H

#include "../Cpu/Types.h"

void MemoryCopy(u8 *source, u8 *dest, int nbytes);
void MemorySet(u8 *dest, u8 val, u32 len);

#endif