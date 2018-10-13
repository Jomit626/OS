#ifndef _UILTS
#define _UILTS

// data types
typedef unsigned    char u8;
typedef             char s8;
typedef unsigned    short u16;
typedef             short s16;
typedef unsigned    int u32;
typedef             int s32;

//can be faster
void memory_copy(char *source, char *dest, int nbytes);
void int_to_ascii(u32 i,char* str);
void str_reverse(char *str);

//Debug
void debug();

// bit contral
#define Lower16(X) ((u16)((X) & 0xffff))
#define Upper16(X) ((u16)(((X) >> 16) & 0xffff))

//Kernel segment selector
#define KERNEL_C 0x8
#define KERNEL_D 0x16

#endif