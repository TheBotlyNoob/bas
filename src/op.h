#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER

#include <stdint.h>
#include <cpu.h>

void op_cls(c8_cpu_t *cpu);
void op_rts(c8_cpu_t *cpu);

void op_jp(c8_cpu_t *cpu, uint16_t addr);

void op_call(c8_cpu_t *cpu, uint16_t addr);

void op_se(c8_cpu_t *cpu, uint8_t val1, uint8_t val2);
void op_sne(c8_cpu_t *cpu, uint8_t val1, uint8_t val2);

void op_ld(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);
void op_ld_i(c8_cpu_t *cpu, uint16_t val);

void op_or(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);
void op_xor(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);
void op_and(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);

void op_add(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);
void op_sub(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);

#endif
