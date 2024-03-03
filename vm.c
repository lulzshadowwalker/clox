#include <stdio.h>
#include "vm.h" 
#include "debug.h"

Vm vm;

static void reset_stack() {
  vm.stackTop = vm.stack;
}

void init_vm() {
  reset_stack(); 
}

void free_vm() { }

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do { \
      double b = pop(); \
      double a = pop(); \
      push(a op b); \
    } while (0)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[ ");
      print_value(*slot);
      printf(" ]");
    }
    printf("\n");

    disassemble_instruction(vm.chunk,
                           (int)(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
      case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        print_value(constant);
        printf("\n");
        push(constant); 
        break;
      }
      case OP_ADD: { BINARY_OP(+); break; }
      case OP_SUBTRACT: { BINARY_OP(-); break; } 
      case OP_MULTIPLY: { BINARY_OP(*); break; }
      case OP_DIVIDE: { BINARY_OP(/); break; }
      case OP_NEGATE: { push(-pop()); break; }
      case OP_RETURN: {
        print_value(pop());
        printf("\n");
        return INTERPRET_OK;
      }
    }
  }

#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}