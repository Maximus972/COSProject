global asm_timer_handler

; C-handlers
extern timer_handler

section .text

; Keyboard interrupt handler
asm_timer_handler:
    pusha
    call timer_handler ; C-handler
    popa
    iretd

