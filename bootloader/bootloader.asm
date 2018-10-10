[org 0x7c00]
__bootloaderStart:
    mov bx, Hello
    call Print_String
    mov dx, 0x1234
    call Print_Hex
    jmp $

%include "./bootloader/print_hex16.asm"
%include "./bootloader/print_string.asm"



Hello:
    db 'Hello!',0

; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0
; Magic number
dw 0xaa55 