global outb, outw, outd, in_out_wait 
global inb, inw, ind

section .text

outb:
    push ebp
    mov ebp, esp
    mov dx, WORD [ebp + 8]
    mov al, BYTE [ebp + 12]
    out dx, al
    pop ebp
    ret

outw:
    push ebp
    mov ebp, esp
    mov dx, WORD [ebp + 8]
    mov ax, WORD [ebp + 12]
    out dx, ax
    pop ebp
    ret

outd:
    push ebp
    mov ebp, esp
    mov dx, WORD [ebp + 8]
    mov eax, DWORD [ebp + 12]
    out dx, eax
    pop ebp
    ret

in_out_wait:
    mov dx, 0x80
    mov ax, 0
    out dx, ax

inb:
    push ebp
    mov ebp, esp
    mov dx, WORD [ebp + 8]
    xor eax, eax
    in al, dx
    pop ebp
    ret

inw:
    push ebp
    mov ebp, esp
    mov dx, WORD [ebp + 8]
    xor eax, eax
    in ax, dx
    pop ebp
    ret

ind:
    push ebp
    mov ebp, esp
    mov dx, WORD [ebp + 8]
    xor eax, eax
    in eax, dx
    pop ebp
    ret