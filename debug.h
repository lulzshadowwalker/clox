#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disassemble_chunk(Chunk* chunk, const char* name);

/** 
  * it returns the offset of the next instruction.
  * this is because, as we’ll see later, instructions can have different sizes.
  */
int disassemble_instruction(Chunk* chunk, int offset);

#endif
