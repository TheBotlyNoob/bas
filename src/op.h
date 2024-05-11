#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER

#include <stdint.h>
#include <cpu.h>

// Clear the display.
//
// `00E0`
void op_cls(c8_cpu_t *cpu);
// Return from a subroutine.
//
// The interpreter sets the program counter to the address at the top of the stack,
// then subtracts 1 from the stack pointer.
//
// `00EE`
void op_rts(c8_cpu_t *cpu);

// Jump to location `addr`.
//
// The interpreter sets the program counter to `addr`.
void op_jp(c8_cpu_t *cpu, uint16_t addr);

// Call subroutine at `addr`.
//
// The interpreter increments the stack pointer,
// then puts the current `PC` on the top of the stack.
// The `PC` is then set to `addr`.
void op_call(c8_cpu_t *cpu, uint16_t addr);

// Skip next instruction if `val1` == `val2`.
//
// The interpreter compares `val1` and `val2`, and if they are equal,
// increments the `PC` by 2.
void op_se(c8_cpu_t *cpu, uint8_t val1, uint8_t val2);
// Skip next instruction if `val1` != `val2`.
//
// The interpreter compares `val1` to `val2`, and if they are not equal,
// increments the `PC` by 2.
void op_sne(c8_cpu_t *cpu, uint8_t val1, uint8_t val2);

// Set register `reg_n` to `val`.
//
// The interpreter puts the value `val` into register `reg_n`.
void op_ld(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);
// Set register `reg_n` to the value of register `reg_n` + `val`.
void op_add(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);

// Set register `reg_n1` the value of register `reg_n2` OR the value of register `reg_n1`.
//
// Performs a bitwise OR on the values of `reg_n1` and `reg_n2`,
// then stores the result

#endif
