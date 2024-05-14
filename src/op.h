#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER

#include <stdint.h>
#include <cpu.h>

void op_cls(c8_cpu_t *cpu);
void op_ret(c8_cpu_t *cpu);

void op_jp(c8_cpu_t *cpu, uint16_t addr);

void op_call(c8_cpu_t *cpu, uint16_t addr);

void op_se(c8_cpu_t *cpu, uint8_t val1, uint8_t val2);
void op_sne(c8_cpu_t *cpu, uint8_t val1, uint8_t val2);

void op_ld(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);
void op_ld_i(c8_cpu_t *cpu, uint16_t val);
void op_ld_reg_dt(c8_cpu_t *cpu, uint8_t reg_n);
void op_ld_dt_reg(c8_cpu_t *cpu, uint8_t reg_n);
void op_ld_st(c8_cpu_t *cpu, uint8_t val);
void op_ld_dig(c8_cpu_t *cpu, uint8_t reg_n);
void op_ld_bcd(c8_cpu_t *cpu, uint8_t reg_n);
void op_ld_reg_mem(c8_cpu_t *cpu, uint8_t max_reg_n);
void op_ld_mem_reg(c8_cpu_t *cpu, uint8_t max_reg_n);

void op_or(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);
void op_xor(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);
void op_and(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);

void op_shr(c8_cpu_t *cpu, uint8_t reg_n);
void op_shl(c8_cpu_t *cpu, uint8_t reg_n);

void op_add(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);
void op_add_i(c8_cpu_t *cpu, uint8_t reg_n);

void op_sub(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val);

void op_rnd(c8_cpu_t *cpu, uint8_t reg_n, uint8_t mask);

void op_drw(c8_cpu_t *cpu, uint8_t reg_n_x, uint8_t reg_n_y, uint8_t sprite_rows);

void op_skp(c8_cpu_t *cpu, uint8_t reg_n);
void op_sknp(c8_cpu_t *cpu, uint8_t reg_n);

#endif
