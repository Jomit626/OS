#include "ISR.h"
#include "../drivers/screen.h"
#include "../kernel/uilts.h"

void ISR_install(){
    
    IDT_set_gate(0, (u32)isr0);
    IDT_set_gate(1, (u32)isr1);
    IDT_set_gate(2, (u32)isr2);
    IDT_set_gate(3, (u32)isr3);
    IDT_set_gate(4, (u32)isr4);
    IDT_set_gate(5, (u32)isr5);
    IDT_set_gate(6, (u32)isr6);
    IDT_set_gate(7, (u32)isr7);
    IDT_set_gate(8, (u32)isr8);
    IDT_set_gate(9, (u32)isr9);
    IDT_set_gate(10, (u32)isr10);
    IDT_set_gate(11, (u32)isr11);
    IDT_set_gate(12, (u32)isr12);
    IDT_set_gate(13, (u32)isr13);
    IDT_set_gate(14, (u32)isr14);
    IDT_set_gate(15, (u32)isr15);
    IDT_set_gate(16, (u32)isr16);
    IDT_set_gate(17, (u32)isr17);
    IDT_set_gate(18, (u32)isr18);
    IDT_set_gate(19, (u32)isr19);
    IDT_set_gate(20, (u32)isr20);
    IDT_set_gate(21, (u32)isr21);
    IDT_set_gate(22, (u32)isr22);
    IDT_set_gate(23, (u32)isr23);
    IDT_set_gate(24, (u32)isr24);
    IDT_set_gate(25, (u32)isr25);
    IDT_set_gate(26, (u32)isr26);
    IDT_set_gate(27, (u32)isr27);
    IDT_set_gate(28, (u32)isr28);
    IDT_set_gate(29, (u32)isr29);
    IDT_set_gate(30, (u32)isr30);
    IDT_set_gate(31, (u32)isr31);
    
    IDT_load_reg();
}

void ISR_handler(registers_t t){
    
    print_string("str");
}

void PCI_sent_EOI(u8 irq){
    // if irq come from slave pci,sent both
    if (irq >=8){
        port_byte_out(SLAVE_PCI_DATA, PCI_EOI);
    }
    port_byte_out(MASTER_PCI_DATA, PCI_EOI);
}