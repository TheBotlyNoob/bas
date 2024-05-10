#include <stdbool.h>
#include <stdio.h>

#include "cpu.h"
#include "op.h"

int run_op(c8_cpu_t *cpu, uint16_t op)
{

    // lower byte lower nyble
    uint32_t ll_n = op >> 12;

    printf("%x\n", ll_n);
    // lower byte upper nyble
    uint8_t lu_n = (op >> 4) & 0x0F;
    printf("%x\n", lu_n);
    // upper byte lower nyble
    uint8_t ul_n = (op >> 4) & 0xF0;
    printf("%x\n", ul_n);

    // upper byte upper nyble
    uint8_t uu_n = op & 0x000f;

    switch (ll_n) // get first nyble
    {
    case 0x0: //
        // if (uu_n == 0)
        // {
        //     inst_cls();
        // }
        // else
        // {
        //     inst_ret();
        // }
        return 1;
        break;
    case 0x1:
        op_jp(cpu, op & 0x0fff);
    default:
        return 1;
    }
    return 0;
}

void run_cpu(c8_cpu_t cpu)
{
    while (true)
    {
        uint16_t op = cpu.mem[cpu.pc] << 8 | (cpu.mem[cpu.pc + 1]);
        printf("running opcode: 0x%04x; pc = 0x%x\n", op, cpu.pc);
        cpu.pc += 2;

        if (run_op(&cpu, op) != 0)
        {
            printf("opcode not found: 0x%04x\n", op);
            break;
        }
        break;
    }
}
