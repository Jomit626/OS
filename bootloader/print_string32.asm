[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

;print string EBX
print_string32:
    push ax
    push edx
    push ebx 

    mov ah,WHITE_ON_BLACK
    mov edx,VIDEO_MEMORY
    print_string32_Loop1:
    mov al, [ebx]
    cmp al,0
    je print_string32_Loop1END

    mov [edx],ax
    add edx,0x2
    add ebx,0x1

    jmp print_string32_Loop1

    print_string32_Loop1END:
    pop ax
    pop edx
    pop ebx 
    ret