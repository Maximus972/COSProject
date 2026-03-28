global isr0, isr6, isr13, isr14

extern exception_handler

section .text

isr0:
  pusha
  push dword 0
  call exception_handler
  add esp, 4
  popa
  iretd

isr6:
  pusha
  push dword 6
  call exception_handler
  add esp, 4
  popa
  iretd

isr13:
  pusha
  push dword 13
  call exception_handler
  add esp, 4
  popa
  iretd

isr14:
  pusha
  push dword 14
  call exception_handler
  add esp, 4
  popa
  iretd
