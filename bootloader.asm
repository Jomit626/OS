[org 0x7c00]
__bootloaderStart:
    mov bx, Hello
    ;call Print_String
    mov dx, 0x1234
    call Print_Hex
    jmp $


;Func print c style string
;bx address of the string
Print_String:
    pusha
    mov ah, 0x0e
__Loop1:
    mov al, [bx]
    cmp al, 0x0
    je __Loop1End
    int 0x10
    add bx,0x1
    jmp __Loop1
__Loop1End:
    popa
    ret

;Func print num in hex
;dx the num to be printed
Print_Hex:
    pusha
    mov ax,0x0;ax as index
    mov bx,Hex_String;string address
__Loop2:
    cmp ax,0x4 ;index < 4
    je __Loop2End
    mov cx,dx
    and cx,0xf

    cmp cx,0xa
    jl __less_then_ten
    add cx,0x61
    sub cx,0xa
    jmp __ifend1
__less_then_ten:
    add cx,0x30
__ifend1:
    mov [bx], cx
    add bx,0x1
    add ax, 0x1
    shr dx,0x4
    jmp __Loop2
__Loop2End:
    mov bx,Hex_String
    call Print_String
    popa
    ret

Hello:
    db 'Hello!',0
Hex_String:
    db '000000000000000',0
; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0
; Magic number
dw 0xaa55 