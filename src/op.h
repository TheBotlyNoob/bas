#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER

#include <stdint.h>
#include <cpu.h>

void op_jp(c8_cpu_t* cpu, uint16_t addr);

#endif
