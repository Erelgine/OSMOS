/*
 * The input/output bridge, in order to communicate with devices.
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "io.hpp" 						// We include the IO header, which is necessary in order to define the functions.

#include "../common/common.hpp" 		// We want to use common ports.

void IO::Port::out(uint_8 val, uint_16 port) {
	asm("outb %1, %0"
	   :
	   : "r" (val), "d" (port));
}

void IO::Port::out(uint_16 val, uint_16 port) {
	asm("outw %1, %0"
	   :
	   : "r" (val), "d" (port));
}

void IO::Port::out(uint_32 val, uint_16 port) {
	asm("outd %1, %0"
	   :
	   : "r" (val), "d" (port));
}

void IO::Port::in(uint_16 port, uint_8 *val) {
	uint_8 vwl;
	asm("inb %0, %1"
	   : "=a" (vwl)
	   : "d" (port));
	*val = vwl;
}

void IO::Port::in(uint_16 port, uint_16 *val) {
	uint_16 vwl;
	asm("inw %0, %1"
	   : "=a" (vwl)
	   : "d" (port));
	*val = vwl;
}

void IO::Port::in(uint_16 port, uint_32 *val) {
	uint_32 vwl;
	asm("ind %0, %1"
	   : "=a" (vwl)
	   : "d" (port));
	*val = vwl;
}

IO::Port::Port(uint_16 port) {
	this->port = port;
}

void IO::Port::out(uint_8 val) {
	IO::Port::out(val, this->port);
}

void IO::Port::out(uint_16 val) {
	IO::Port::out(val, this->port);
}

void IO::Port::out(uint_32 val) {
	IO::Port::out(val, this->port);
}

void IO::Port::in(uint_8 *val) {
	IO::Port::in(this->port, val);
}

void IO::Port::in(uint_16 *val) {
	IO::Port::in(this->port, val);	
}

void IO::Port::in(uint_32 *val) {
	IO::Port::in(this->port, val);
}