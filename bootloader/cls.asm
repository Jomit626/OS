[bits 32]
VIDEO_MEMORY equ 0xb8000
VIDEO_MEMORY_END equ 0xb8FA0
;WHITE_ON_BLACK equ 0x0d
;cls the VGA memo
cls:
    push ax
    push edx

    mov ah,0x0f
    mov al,0x0
    mov edx,VIDEO_MEMORY
    cls_Loop1:
    mov [edx],ax

    cmp edx,VIDEO_MEMORY_END
    je cls_Loop1END

    add edx,0x2

    jmp cls_Loop1

    cls_Loop1END:
    pop ax
    pop edx
    ret