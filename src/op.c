#include "op.h"

void op_jp(c8_cpu_t *cpu, uint16_t addr)
{
    cpu->pc = addr;
}
