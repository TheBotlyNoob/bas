#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef CHIP8_DETERMINISTIC
#include <time.h>
#endif

#include "cpu.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    uint8_t mem[MEM_SIZE - START_LOC];
    uint8_t i;
    size_t read;

    if (argc != 2)
    {
        printf("USAGE: %s <ch8 file>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("error opening chip-8 file.\n");
        return 1;
    }
    read = fread(&mem, sizeof(uint8_t), MEM_SIZE - START_LOC, fp);
    if (read == 0)
    {
        printf("error reading chip-8 file.\n");
        return 1;
    }
    printf("read %ld bytes from chip-8 file.\n", read);
    fclose(fp);

    c8_cpu_t cpu;

    // for (i = 0; i < MEM_SIZE; i++)
    // {
    //     cpu.mem[i] = 0;
    // }

    memcpy(&cpu.mem[START_LOC], &mem, read);

    cpu.mem[START_LOC] = 0x00;
    cpu.mem[START_LOC + 1] = 0xE0;

    cpu.pc = START_LOC;
    cpu.sp = STACK_SIZE - 1;
    cpu.reg_i = 0;
    for (int i = 0; i < 16; i++)
    {
        cpu.general_reg[i] = 0;
    };

#ifdef CHIP8_DETERMINISTIC
    printf("running in deterministic mode.");
    srand(1)
#else
    srand(time(NULL));
#endif

        run_cpu(cpu);
}
