#ifndef CPU_HEADER
#define CPU_HEADER

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

// could be 0x600, if using ETI 660 computer.
#define START_LOC 0x200
#define MEM_SIZE 0xFFF
#define STACK_SIZE 16

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

typedef struct
{
    // 0x000 to 0x1FF reserved for interpreter.
    uint8_t mem[MEM_SIZE];
    // reg 16 is used as status; shouldn't be used by regular programs.
    uint8_t general_reg[16];
    uint16_t reg_i;
    uint16_t stack[STACK_SIZE];
    uint16_t pc;
    uint8_t sp;

    uint8_t delay_timer;
    uint8_t sound_timer;

    uint64_t last_tick_time_ms;

    uint8_t display[DISPLAY_HEIGHT][DISPLAY_WIDTH / 8];
} c8_cpu_t;

void run_cpu(c8_cpu_t cpu);

// pops the address at the bottom of the stack, and increments the stack pointer.
// If the stack is empty, the program will crash.
uint16_t cpu_pop(c8_cpu_t *cpu);
// pushes an address to the bottom of the stack, and decrements the stack pointer.
// returns `false` if the stack is full.
void cpu_push(c8_cpu_t *cpu, uint16_t addr);

#endif
