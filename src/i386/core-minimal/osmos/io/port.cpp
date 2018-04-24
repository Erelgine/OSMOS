/*
 * The I/O port communication class
 * Copyright (C) 2018 Alexis BELMONTE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "port.hpp"

#include "../osmos.hpp"

void OSMOS::IO::Port::in(uint16_t port, uint8_t *value) {
	asm("inb ebx, %[port]\n \
		 mov %[value], ebx"
	   : [value] "=a" (value)
	   : [port] "c" (port));
}

void OSMOS::IO::Port::in(uint16_t port, uint16_t *value) {
	asm("inw bx, %[port]\n \
		 mov %[value], bx"
	   : [value] "=a" (value)
	   : [port] "c" (port));
}

void OSMOS::IO::Port::in(uint16_t port, uint32_t *value) {
	asm("ind bl, %[port]\n \
		 mov %[value], bl"
	   : [value] "=a" (value)
	   : [port] "c" (port));
}

void OSMOS::IO::Port::out(uint16_t port, uint8_t value) {
	asm("outb %[port], %[value]"
	   :
	   : [port] "d" (port), [value] "a" (value));
}

void OSMOS::IO::Port::out(uint16_t port, uint16_t value) {
	asm("outw %[port], %[value]"
	   :
	   : [port] "d" (port), [value] "a" (value));	
}
void OSMOS::IO::Port::out(uint16_t port, uint32_t value) {
	asm("outd %[port], %[value]"
	   :
	   : [port] "d" (port), [value] "a" (value));
}