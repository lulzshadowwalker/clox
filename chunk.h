#ifndef clox_chunk_h
#define clox_chunk_h

#include <stdint.h>

#include "value.h" 

typedef enum {
  OP_CONSTANT,
  OP_RETURN,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NEGATE, 
} OpCode;

typedef struct {
  int count; 
  int capacity;
  uint8_t* code; 
  int* lines; 
  
  // constants pool
  ValueArray constants;
} Chunk; 

void init_chunk(Chunk* chunk); 
void write_chunk(Chunk* chunk, uint8_t byte, int line); 
void free_chunk(Chunk* chunk);
int add_constant(Chunk* chunk, Value value); 

#endif
