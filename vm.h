#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"
#include <stdint.h>

#define STACK_MAX 256 

typedef struct {
  Chunk *chunk;

  /**
   * actual real C pointer pointing right into the middle of the bytecode array
   * instead of somethinglike like an integer index because it’s faster to
   * dereference a pointer than look up an element in an array by index
   */
  /**
   * "The thing about local variables is that the compiler optimizes them to be
   * allocated from the registers if possible, or from the cache if not. This is
   * why local variables are faster."
   * https://stackoverflow.com/questions/41147208/are-global-variables-faster-than-local-variables-in-c
   */
  uint8_t *ip;
  
  /**
   * The pointer points at the array element just past the element containing the top value on the stack.
   * That seems a little odd, but almost every implementation does this.
   * It means we can indicate that the stack is empty by pointing at element zero in the array.
   */
  /**
   * It is allowed and well-specified to have an array pointer that points just past the end of an array. 
   */
  Value stack[STACK_MAX];
  Value* stackTop; 
} Vm;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void init_vm();
void free_vm();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif
