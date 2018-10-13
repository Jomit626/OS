#ifndef _UILTS
#define _UILTS

#include <stdint.h>

// data types
typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int16_t s32;

//can be faster
void memory_copy(char *source, char *dest, int nbytes);
void int_to_ascii(u32 i,char* str);
void str_reverse(char *str);

//Debug
void debug();
void print_in_bit(u32 i);
// bit contral
#define Lower16(X) ((u16)((X) & 0xffff))
#define Upper16(X) ((u16)(((X) >> 16) & 0xffff))

//Kernel segment selector
#define KERNEL_C 0x8
#define KERNEL_D 0x10

#endif