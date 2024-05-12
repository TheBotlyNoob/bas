#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "op.h"

bool add_will_overflow(uint8_t a, uint8_t b)
{
    if (b > UINT8_MAX - a)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void op_cls(c8_cpu_t *cpu)
{
    printf("\e[1;1H\e[2J");
}
void op_rts(c8_cpu_t *cpu)
{
    uint16_t addr = cpu_pop(cpu);
    cpu->pc = addr - 1;
}

void op_jp(c8_cpu_t *cpu, uint16_t addr)
{
    cpu->pc = addr;
}

void op_call(c8_cpu_t *cpu, uint16_t addr)
{
    cpu_push(cpu, cpu->pc + 1);
    cpu->pc = addr;
}

void op_se(c8_cpu_t *cpu, uint8_t val1, uint8_t val2)
{
    if (val1 == val2)
    {
        cpu->pc += 2;
    }
}
void op_sne(c8_cpu_t *cpu, uint8_t val1, uint8_t val2)
{
    if (val1 != val2)
    {
        cpu->pc += 2;
    }
}

void op_ld(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    cpu->general_reg[reg_n] = val;
}
void op_ld_i(c8_cpu_t *cpu, uint16_t val)
{
    cpu->reg_i = val;
}

void op_or(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    cpu->general_reg[reg_n] = cpu->general_reg[reg_n] | val;
}
void op_xor(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    cpu->general_reg[reg_n] = cpu->general_reg[reg_n] ^ val;
}
void op_and(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    cpu->general_reg[reg_n] = cpu->general_reg[reg_n] & val;
}

void op_add(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    if (cpu->general_reg[reg_n] > UINT8_MAX - val)
    {
        cpu->general_reg[0xF] = 1;
    }
    cpu->general_reg[reg_n] = cpu->general_reg[reg_n] + val;
}
void op_sub(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    if (val > cpu->general_reg[reg_n])
    {
        cpu->general_reg[0xF] = 1;
    }
    cpu->general_reg[reg_n] = cpu->general_reg[reg_n] - val;
}
