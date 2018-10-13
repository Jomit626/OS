#ifndef _IDT
#define _IDT
#include "../kernel/uilts.h"

#define IDT_ENTRIES 256
// IDT entrise
typedef struct {
   u16 offset_1; // offset bits 0..15
   u16 selector; // a code segment selector in GDT or LDT
   u8 zero;      // unused, set to 0
   u8 type_attr; // type and attributes, see below
   u16 offset_2; // offset bits 16..31
}__attribute__((packed)) IDT_gate;


// load iwt `lidt`
typedef struct {
    u16 limit;
    u32 base;
}__attribute__((packed)) IDT_reg;

IDT_gate idts[IDT_ENTRIES];
IDT_reg idt_reg;
// public func
void IDT_set_gate(int n, u32 handler);
void IDT_load_reg();

#endif