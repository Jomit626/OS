#include "IDT.h"

void IDT_set_gate(int n, u32 handler){
    idts[n].offset_1 = Lower16(handler);
    idts[n].selector = KERNEL_C;
    idts[n].zero = 0;
    idts[n].type_attr = 0x8e;
    idts[n].offset_2 = Upper16(handler);
}
void IDT_load_reg(){
    idt_reg.base = (u32)(&idts);
    idt_reg.limit = IDT_ENTRIES * sizeof(IDT_gate) - 1;
    __asm__ __volatile__("lidtl (%0)" ::"r"(&idt_reg));
    //__volatile__ tells gcc not to opt it
}