#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "op.h"

int run_op(c8_cpu_t *cpu, uint16_t op)
{

    // see #3.0 in the ref for what these mean
    uint16_t nnn = op & 0x0FFF;
    uint8_t kk = op >> 8;
    uint8_t x = (op >> 8) & 0x0F;
    uint8_t y = op & 0xF0 >> 4;
    uint8_t n = op & 0x000F;
    // my own; the first nyble
    uint8_t f = (op >> 12);

    switch (f)
    {
    case 0x0:
        if (n == 0)
        {
            op_cls(cpu);
        }
        else
        {
            op_rts(cpu);
        }
        break;
    case 0x1:
        op_jp(cpu, nnn);
        break;
    case 0x2:
        op_call(cpu, nnn);
        break;
    case 0x3:
        op_se(cpu, x, kk);
        break;
    case 0x4:
        op_sne(cpu, x, kk);
        break;
    case 0x5:
        op_se(cpu, x, cpu->general_reg[y]);
        break;
    case 0x6:
        op_ld(cpu, x, kk);
        break;
    case 0x7:
        op_add(cpu, x, kk);
        break;
    case 0x8:
        switch (n)
        {
        case 0x00:
            op_ld(cpu, x, cpu->general_reg[y]);
            break;
        case 0x01:
            op_or(cpu, x, cpu->general_reg[y]);
            break;
        case 0x02:
            op_and(cpu, x, cpu->general_reg[y]);
            break;
        case 0x03:
            op_xor(cpu, x, cpu->general_reg[y]);
            break;
        case 0x04:
            op_add(cpu, x, cpu->general_reg[y]);
            break;
        case 0x05:
            op_sub(cpu, x, cpu->general_reg[y]);
            break;
        default:
            return 1;
        }
        break;
    case 0x9:
        op_sne(cpu, x, cpu->general_reg[y]);
        break;
    case 0xA:
        op_ld_i(cpu, nnn);
        break;
    case 0xB:
        op_jp(cpu, nnn + cpu->general_reg[0]);
        break;
    case 0xC:
        // op_rand(x, y);

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

uint16_t cpu_pop(c8_cpu_t *cpu)
{
    if (cpu->sp == STACK_SIZE - 1)
    {
        printf("STACK UNDERFLOW AT %04x", cpu->pc - 2);
        exit(1);
    }

    uint8_t val = cpu->mem[cpu->sp];

    cpu->sp += sizeof(uint16_t);

    return val;
}
bool cpu_push(c8_cpu_t *cpu, uint16_t addr)
{
    if (cpu->sp == 0)
    {
        printf("STACK OVERFLOW AT %04x", cpu->pc - 2);
        return false;
    }

    cpu->mem[cpu->sp] = addr;

    cpu->sp -= sizeof(uint16_t);

    return true;
}
