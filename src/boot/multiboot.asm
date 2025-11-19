; multiboot.asm
bits 32                     ; Генерируем 32-битный код
section .multiboot          ; Multiboot-заголовок
    align 4
    dd 0x1BADB002          ; Магическое число Multiboot
    dd 0x00                ; Флаги
    dd -(0x1BADB002 + 0x00) ; Контрольная сумма

section .text
global start
extern kmain               ; Объявляем внешнюю функцию kmain из C

start:
    cli                    ; Отключаем прерывания
    mov esp, stack_top     ; Устанавливаем указатель стека
    call kmain             ; Вызываем главную функцию ядра
    hlt                    ; Останавливаем процессор, если kmain вернет управление

section .bss
align 16
stack_bottom:
    resb 16384             ; Резервируем 16 КБ под стек
stack_top: 