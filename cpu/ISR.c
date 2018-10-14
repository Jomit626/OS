#include "ISR.h"
#include "../drivers/screen.h"
#include "../kernel/uilts.h"

isr_t interrupt_handlers[IDT_ENTRIES];

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

    PIC_remap(0x20, 0x28);
    //port_byte_out(0x20, 0x11);
    //port_byte_out(0xA0, 0x11);
    //port_byte_out(0x21, 0x20);
    //port_byte_out(0xA1, 0x28);
    //port_byte_out(0x21, 0x04);
    //port_byte_out(0xA1, 0x02);
    //port_byte_out(0x21, 0x01);
    //port_byte_out(0xA1, 0x01);
    //port_byte_out(0x21, 0x0);
    //port_byte_out(0xA1, 0x0);
    
    IDT_set_gate(32, (u32)irq0);
    IDT_set_gate(33, (u32)irq1);
    IDT_set_gate(34, (u32)irq2);
    IDT_set_gate(35, (u32)irq3);
    IDT_set_gate(36, (u32)irq4);
    IDT_set_gate(37, (u32)irq5);
    IDT_set_gate(38, (u32)irq6);
    IDT_set_gate(39, (u32)irq7);
    IDT_set_gate(40, (u32)irq8);
    IDT_set_gate(41, (u32)irq9);
    IDT_set_gate(42, (u32)irq10);
    IDT_set_gate(43, (u32)irq11);
    IDT_set_gate(44, (u32)irq12);
    IDT_set_gate(45, (u32)irq13);
    IDT_set_gate(46, (u32)irq14);
    IDT_set_gate(47, (u32)irq15);

    IDT_load_reg();
    __asm__ volatile("sti");
}

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void ISR_handler(registers_t t){
    print_string("received interrupt: ");
    char s[3];
    int_to_ascii(t.int_no, s);
    print_string(s);
    print_string("\n");
    print_string(exception_messages[t.int_no]);
    print_string("\n");
    if (interrupt_handlers[t.int_no]) {
        interrupt_handlers[t.int_no](t);
    }
}
 
void IRQ_handler(registers_t t){
    // if irq come from slave pci,sent both
    if (t.int_no >= 40) port_byte_out(0xA0, 0x20); /* slave */
    port_byte_out(0x20, 0x20); /* master */

    if (interrupt_handlers[t.int_no]) {
        interrupt_handlers[t.int_no](t);
    }
}

void register_interrupt_handler(u8 n,isr_t handler){
    interrupt_handlers[n] = handler;
    IRQ_clear_mask(n - 32);
}

//---------------------------PCI
/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */
 
#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */
 
/*
arguments:
	offset1 - vector offset for master PIC
		vectors on the master become offset1..offset1+7
	offset2 - same for slave PIC: offset2..offset2+7
*/
void PIC_remap(u8 offset1, u8 offset2)
{
	u8 a1, a2;
 
	a1 = port_byte_in(MASTER_PCI_DATA);                        // save masks
	a2 = port_byte_in(SLAVE_PCI_DATA);
 
	port_byte_out(MASTER_PCI_COM, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	port_byte_out(SLAVE_PCI_COM, ICW1_INIT+ICW1_ICW4);
	io_wait();
	port_byte_out(MASTER_PCI_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	port_byte_out(SLAVE_PCI_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	port_byte_out(MASTER_PCI_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	port_byte_out(SLAVE_PCI_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	port_byte_out(MASTER_PCI_DATA, ICW4_8086);
	io_wait();
	port_byte_out(SLAVE_PCI_DATA, ICW4_8086);
	io_wait();
 
	//port_byte_out(MASTER_PCI_DATA, a1);   // restore saved masks.
	//port_byte_out(SLAVE_PCI_DATA, a2);
    port_byte_out(MASTER_PCI_COM, PCI_EOI);
    port_byte_out(SLAVE_PCI_COM, PCI_EOI);
}

void IRQ_set_mask(u8 IRQline) {
    u16 port;
    u8 value;
 
    if(IRQline < 8) {
        port = MASTER_PCI_DATA;
    } else {
        port = SLAVE_PCI_DATA;
        IRQline -= 8;
    }
    value = port_byte_in(port) | (1 << IRQline);
    port_byte_out(port, value);        
}
 
void IRQ_clear_mask(u8 IRQline) {
    u16 port;
    u8 value;
 
    if(IRQline < 8) {
        port = MASTER_PCI_DATA;
    } else {
        port = SLAVE_PCI_DATA;
        IRQline -= 8;
    }
    value = port_byte_in(port) & ~(1 << IRQline);
    port_byte_out(port, value);        
}
