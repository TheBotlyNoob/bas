#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "op.h"

void op_cls(c8_cpu_t *cpu)
{
    // printf("\e[1;1H\e[2J");
    printf("SCREEN CLEARED\n");
}
void op_ret(c8_cpu_t *cpu)
{
    cpu->pc = cpu_pop(cpu) - 1;
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
void op_ld_reg_dt(c8_cpu_t *cpu, uint8_t reg_n)
{
    cpu->general_reg[reg_n] = cpu->delay_timer;
}
void op_ld_dt_reg(c8_cpu_t *cpu, uint8_t reg_n)
{
    cpu->delay_timer = cpu->general_reg[reg_n];
}
void op_ld_st(c8_cpu_t *cpu, uint8_t val)
{
    cpu->sound_timer = val;
}
void op_ld_dig(c8_cpu_t *cpu, uint8_t reg_n)
{
    printf("TODO: FONT FAMILY");
}
void op_ld_bcd(c8_cpu_t *cpu, uint8_t reg_n)
{
    cpu->mem[cpu->reg_i] = (reg_n / 10 / 10) & 0xF;
    cpu->mem[cpu->reg_i + 1] = (reg_n / 10) & 0xF;
    cpu->mem[cpu->reg_i + 2] = reg_n % 10;
}
void op_ld_reg_mem(c8_cpu_t *cpu, uint8_t max_reg_n)
{
    uint8_t i;
    for (i = 0; i < max_reg_n; ++i)
    {
        cpu->mem[cpu->reg_i + i] = cpu->general_reg[i];
    }
}
void op_ld_mem_reg(c8_cpu_t *cpu, uint8_t max_reg_n)
{
    uint8_t i;
    for (i = 0; i < max_reg_n; ++i)
    {
        cpu->general_reg[i] = cpu->mem[cpu->reg_i + i];
    }
}

void op_or(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    cpu->general_reg[reg_n] |= val;
}
void op_xor(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    cpu->general_reg[reg_n] ^= val;
}
void op_and(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    cpu->general_reg[reg_n] &= val;
}

void op_shr(c8_cpu_t *cpu, uint8_t reg_n)
{
    if (cpu->general_reg[reg_n] & 1 == 1)
    {
        cpu->general_reg[0xF] = 1;
    }
    cpu->general_reg[reg_n] >>= 1;
}
void op_shl(c8_cpu_t *cpu, uint8_t reg_n)
{
    if (cpu->general_reg[reg_n] >> 7 == 1)
    {
        cpu->general_reg[0xF] = 1;
    }
    cpu->general_reg[reg_n] <<= 1;
}

void op_add(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    cpu->general_reg[0xF] = cpu->general_reg[reg_n] > UINT8_MAX - val;

    cpu->general_reg[reg_n] += val;
}
void op_add_i(c8_cpu_t *cpu, uint8_t reg_n)
{
    cpu->reg_i += cpu->general_reg[reg_n];
}

void op_sub(c8_cpu_t *cpu, uint8_t reg_n, uint8_t val)
{
    cpu->general_reg[0xF] = val > cpu->general_reg[reg_n];

    cpu->general_reg[reg_n] = cpu->general_reg[reg_n] - val;
}

void op_rnd(c8_cpu_t *cpu, uint8_t reg_n, uint8_t mask)
{
    cpu->general_reg[reg_n] = (rand() % UINT8_MAX) & mask;
}

void op_drw(c8_cpu_t *cpu, uint8_t reg_n_x, uint8_t reg_n_y, uint8_t sprite_height)
{
    uint8_t i, j, sprite_row, x_idx, y_idx;

    cpu->general_reg[0xF] = 0;

    for (i = 0; i < sprite_height; ++i)
    {
        sprite_height = cpu->mem[cpu->reg_i + i];
        for (j = 0; j < 8; ++j)
        {
            y_idx = (cpu->general_reg[reg_n_y] + j) % DISPLAY_HEIGHT;
            x_idx = (cpu->general_reg[reg_n_x] + i) % DISPLAY_WIDTH;

            cpu->general_reg[0xF] |= (cpu->display[x_idx / 8][y_idx] >> (x_idx % 8)) & 1;

            cpu->display[y_idx][x_idx] ^= sprite_row & (1 << j);
        }
    }
}

void op_skp(c8_cpu_t *cpu, uint8_t reg_n)
{
    printf("TODO: KEYBOARD INPUT; IGNORING");
}
void op_sknp(c8_cpu_t *cpu, uint8_t reg_n)
{
    printf("TODO: KEYBOARD INPUT; IGNORING");
}
