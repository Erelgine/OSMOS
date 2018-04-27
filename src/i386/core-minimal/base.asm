; The base file, a bridge from Assembly to C(++)
; Copyright (C) 2018 Alexis BELMONTE
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <https://www.gnu.org/licenses/>.

; The multiboot2 header, necessary in order to tell to GRUB that it is a valid
; boot binary. Labels are lowercase while variables/data are UPPERCASE.

section .multiboot
header_start:
    align 4
    HEADER_MAGIC             dd 0xE85250D6
    ARCHITECTURE_TYPE         dd 0x0
    HEADER_SIZE                dd (header_end - header_start)
    HEADER_CHECKSUM            dd 0x100000000 - (0xE85250D6 + 0 + (header_end - header_start))

    dw 0                                                                ; Type
    dw 0                                                                ; Flags
    dd 8                                                                ; Size
header_end:

; The stack, pretty much easy. Just allocating 32 KB of memory for it.
section .bss
    align 16
    stack_bottom:
    resb 32767                                                             ; 32 KB stacksize
    stack_top:

; The code. Here, we tell to NASM that we know that kmain is already defined, and also
; say that _start is accessible to GCC
section .text
    extern kboot
    global _start:function (_start.end - _start)

_start:
; We move the stack onto ESP, put the multiboot header address, and then call kmain !
    mov esp, stack_top

    push ebx    ; Push the pointer to the Multiboot structure
    push eax    ; Push the magic value

    call kboot

; Out of kmain, we want to stop the CPU. First, we clear the interrupts.
    cli

.end:
; We want to halt the CPU.
    hlt
; It didn't work, so we jump infinitly here.
    jmp $
; It didn't work again, so we restart to the beggining
    jmp .end
; And if it DIDN'T work, the CPU is bad :(