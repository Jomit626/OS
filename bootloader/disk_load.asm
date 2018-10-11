;load DH sectors to ES:BX from drive DL
[bits 16]
disk_load:
    pusha 
    push dx 

    mov ah,0x02     ;BIOS read sector function
    mov al,dh       ;read dh sectors
    mov ch,0x0        ;cylinder 0
    mov dh,0x0        ;track 0
    mov cl,0x2        ;sector 2(after boot secor) 
    int 0x13
    
    jc disk_error
    
    pop dx
    cmp dh,al
    jne disk_error

    popa
    
    ret
disk_error:
    mov bx, DISK_ERROR_MSG
    call Print_String 
    jmp $

DISK_ERROR_MSG db "Disk read error!", 0

