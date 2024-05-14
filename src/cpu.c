#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "cpu.h"
#include "op.h"

int run_op(c8_cpu_t *cpu, uint16_t op)
{

    // see #3.0 in the ref for what these mean
    uint16_t nnn = op & 0xFFF;
    uint8_t kk = op & 0xFF;
    uint8_t x = (op >> 8) & 0x0F;
    uint8_t y = op & 0xF0 >> 4;
    uint8_t n = op & 0xF;
    // my own; the first nyble
    uint8_t f = (op >> 12);

    switch (f)
    {
    case 0x0:
        switch (nnn)
        {
        case 0x0E0:
            op_cls(cpu);
            break;
        case 0x0EE:
            op_ret(cpu);
            break;
        default:
            return 1;
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
        if (n == 0x0)
        {
            op_se(cpu, x, cpu->general_reg[y]);
        }
        else
        {
            return 1;
        }
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
        case 0x0:
            op_ld(cpu, x, cpu->general_reg[y]);
            break;
        case 0x1:
            op_or(cpu, x, cpu->general_reg[y]);
            break;
        case 0x2:
            op_and(cpu, x, cpu->general_reg[y]);
            break;
        case 0x3:
            op_xor(cpu, x, cpu->general_reg[y]);
            break;
        case 0x4:
            op_add(cpu, x, cpu->general_reg[y]);
            break;
        case 0x5:
            op_sub(cpu, x, cpu->general_reg[y]);
            break;
        case 0x6:
            op_shr(cpu, x);
            break;
        case 0x7:
            printf("NOT IMPLEMENTED");
            return 1;
            op_sub(cpu, y, cpu->general_reg[x]);
            break;
        case 0xE:
            op_shl(cpu, x);
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
        op_rnd(cpu, x, y);
        break;
    case 0xD:
        op_drw(cpu, x, y, n);
        break;
    case 0xE:
        switch (n)
        {
        case 0xE:
            op_skp(cpu, x);
            break;
        case 0x1:
            op_sknp(cpu, x);
            break;
        default:
            return 1;
        }
        break;
    case 0xF:
        switch (kk)
        {
        case 0x07:
            op_ld_reg_dt(cpu, x);
            break;
        case 0x0A:
            printf("TODO: LD K");
            break;
        case 0x15:
            op_ld_dt_reg(cpu, x);
            break;
        case 0x18:
            op_ld_st(cpu, x);
            break;
        case 0x1E:
            op_add_i(cpu, x);
            break;
        case 0x29:
            op_ld_dig(cpu, x);
            break;
        case 0x33:
            op_ld_bcd(cpu, x);
            break;
        case 0x55:
            op_ld_reg_mem(cpu, x);
            break;
        case 0x65:
            op_ld_mem_reg(cpu, x);
            break;
        default:
            return 1;
        }
        break;
    default:
        return 1;
    }
    return 0;
}

void get_now_ms(struct timeval *now, uint64_t *ms)
{
    gettimeofday(now, NULL);
    *ms = 1000 * now->tv_sec + now->tv_usec / 1000;
}

void run_cpu(c8_cpu_t cpu)
{
    struct timeval now;
    uint64_t now_ms;

    get_now_ms(&now, &now_ms);

    while (true)
    {
        do
        {
            get_now_ms(&now, &now_ms);
            // printf("%d\n", now_ms);
        } while (now_ms < cpu.last_tick_time_ms + 60);

        uint16_t op = cpu.mem[cpu.pc] << 8 | (cpu.mem[cpu.pc + 1]);
        // printf("running opcode: 0x%04x; pc = 0x%04x\n", op, cpu.pc);

        cpu.pc += 2;

        if (run_op(&cpu, op) != 0)
        {
            printf("opcode not found: 0x%04x\n", op);
            break;
        }

        // todo: do this for realsies; don't hardcode for test rom
        if (op == 0xdab4)
        {
            printf("\e[1;1H\e[2J");
            for (int i = 0; i < DISPLAY_HEIGHT; ++i)
            {
                for (int j = 0; j < DISPLAY_WIDTH; ++j)
                {
                    if (cpu.display[i][j] == 1)
                    {
                        printf("█");
                    }
                    else
                    {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }

        cpu.last_tick_time_ms = now_ms;
    }
}

void u16_to_be(uint8_t *buf, uint16_t val)
{
    buf[0] = val & 0xFF;
    buf[1] = val >> 8;
}
uint16_t be_to_u16(uint8_t *buf)
{
    return buf[0] | buf[1] << 8;
}

uint16_t cpu_pop(c8_cpu_t *cpu)
{

    if (cpu->sp == STACK_SIZE - 1)
    {
        printf("STACK UNDERFLOW AT %04x\n", cpu->pc - 2);
        exit(1);
    }

    cpu->sp += sizeof(uint16_t);

    uint16_t val = be_to_u16(&cpu->mem[cpu->sp]);

    return val;
}
void cpu_push(c8_cpu_t *cpu, uint16_t addr)
{
    if (cpu->sp == 0)
    {
        printf("STACK OVERFLOW AT %04x\n", cpu->pc - 2);
        exit(1);
    }

    u16_to_be(&cpu->mem[cpu->sp], addr);

    cpu->sp -= sizeof(uint16_t);
}
