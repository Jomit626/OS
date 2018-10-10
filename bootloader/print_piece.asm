[bits 32]
VIDEO_MEMORY equ 0xb8000
;print row:al,col:ah,color:bx
print_piece:
    push eax
    push ax
    mov eax,VIDEO_MEMORY
    mul al,0x50
    add al,bx
    mul al,2
    add eax,al
    mov [eax],bx
    pop eax
    pop ax
