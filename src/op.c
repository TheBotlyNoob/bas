#include <stdio.h>
#include <stdlib.h>

#include "op.h"

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
