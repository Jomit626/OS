[org 0x7c00]

KERNEL_OFFSET equ 0x1000

[bits 16]
    mov [BOOT_DRIVE], dl

    mov bx, MSG_REAL_MODE
    call Print_String
    call load_kernel
    call switch_to_PM

%include "./bootloader/print_string16.asm"
%include "./bootloader/gdt.asm"
%include "./bootloader/switch_to_PM.asm"
%include "./bootloader/print_string32.asm"
;%include "./bootloader/cls.asm"
%include "./bootloader/disk_load.asm"

load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call Print_String
    mov bx,KERNEL_OFFSET
    mov dh,47
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    ;call cls
    mov ebx, MSG_PROT_MODE
    call print_string32

    call KERNEL_OFFSET
    jmp $



;var
    MSG_REAL_MODE db "Started in 16-bit Real Mode", 0 
    MSG_PROT_MODE db "Successfully landed in 32-bit Protected Mode!!!", 0 
    MSG_LOAD_KERNEL db "Loading kernel into memory.", 0
BOOT_DRIVE:
    db 0

; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0
; Magic number
dw 0xaa55 