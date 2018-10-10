[org 0x7c00]
[bits 16]
   ; mov [BOOT_DRIVE], dl

    mov bx, Hello
    call Print_String
    
    call switch_to_PM

%include "./bootloader/print_string16.asm"
%include "./bootloader/gdt.asm"
%include "./bootloader/switch_to_PM.asm"
%include "./bootloader/print_string32.asm"

[bits 32]
BEGIN_PM:
    mov ebx, Hello
    call print_string32
    jmp $



;var
Hello:
    db 'Hello!',0
BOOT_DRIVE:
    db 0

; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0
; Magic number
dw 0xaa55 