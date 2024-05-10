#ifndef CPU_HEADER
#define CPU_HEADER

#include <stdint.h>

// could be 0x600, if using ETI 660 computer.
#define START_LOC 0x200
#define MEM_SIZE 0xFFF

typedef struct
{
    // 0x000 to 0x1FF reserved for interpreter.
    uint8_t mem[MEM_SIZE];
    // reg 16 is used as status; shouldn't be used by regular programs.
    uint8_t general_reg[16];
    uint16_t reg_i;
    uint16_t stack[16];
    uint16_t pc;
    uint8_t sp;
} c8_cpu_t;

void run_cpu(c8_cpu_t cpu);

#endif
