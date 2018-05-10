; The constructor/destructor's caller, for the C++ kernel
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

; We want to use G++'s generated constructors and destructors from C++ classes
extern start_ctors
extern end_ctors
extern start_dtors
extern end_dtors

cs_call:
    push eax
    mov eax, start_ctors
    jmp .cs_while
    
    .cs_call:
        call [eax]
        add eax, 4
    
    .cs_while:
        cmp eax, end_ctors
        jb .cs_call

    .cs_end:
        xor eax, eax
        pop eax
        ret

ds_call:
    push eax
    mov eax, end_dtors
    jmp .ds_while

    .ds_call:
        sub eax, 4
        call [eax]

    .ds_while:
        cmp eax, start_dtors
        ja .ds_call

    .ds_end:
        xor eax, eax
        pop eax
        ret