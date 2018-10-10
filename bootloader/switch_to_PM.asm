[bits 16]
switch_to_PM:
    cli;disable int
    lgdt [gdt_descriptior];pass gdt
    mov eax, cr0;turn protected mode on
    or eax,0x1
    mov cr0,eax
    jmp CODE_SEG:init_PM;issue a far jump to flash the pipeline
[bits 32]
init_PM:
    mov ax, DATA_SEG ; Now in PM, our old segments are meaningless , 
    mov ds, ax ; so we point our segment registers to the 
    mov ss, ax ; data selector we defined in our GDT 
    mov es, ax 
    mov fs, ax 
    mov gs, ax

    mov ebp, 0x90000 ; Update our stack position so it is right 
    mov esp, ebp ; at the top of the free space.

    call BEGIN_PM ; Finally , call some well -known label