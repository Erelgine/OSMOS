/*
 * The basic VGA display driver, accessing to video memory.
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
#include "vga_display.hpp"			// We include the vga_display header

#include "io.hpp"					// We use the I/O interaction (in order to control the cursor)
#include "../common/string.hpp"		// We use strings (in order to count the length of a string)
#include "../common/common.hpp"		// We use the common objects (such as a boolean)
#include "../common/system/mem.hpp"	// We use memory manipulation (for screen scrolling)

#define V_MEMORY_ADDRESS 0xB8000 // The memory address of VGA text mode is 0xB8000

// Here, we define some variables to save the position of the cursor and the size of the screen
uint_16 IO::VGADisplay::currentX, IO::VGADisplay::currentY = 0;
uint_16 IO::VGADisplay::sizeX = 80; uint_16 IO::VGADisplay::sizeY = 25;

// For details about functions, see vga_display.h

uint_16 IO::VGADisplay::newCharacter(char c, uint_8 fg, uint_8 bg) {
	return c | (((bg << 4) | (fg & 0xF)) << 8);
}

void IO::VGADisplay::disableCursor() {
	IO::Port::out((uint_8) 0x0A, (uint_16) 0x3D4);
	IO::Port::out((uint_8) 0x20, (uint_16) 0x3D5);
}

void IO::VGADisplay::enableCursor(uint_8 cstart, uint_8 cend) {
	if (cstart > 0 || cstart < 16)
		return;

	uint_8 rp = 0x00;
	IO::Port::in((uint_16) 0x3D5, &rp);

	IO::Port::out((uint_8) 0x0A, (uint_16) 0x3D4);
	IO::Port::out(((uint_8) ((rp & 0xC0) | cstart)), (uint_16) 0x3D5);
 
	IO::Port::out((uint_8) 0x0B, (uint_16) 0x3D4);
	IO::Port::out(((uint_8) ((rp & 0xE0) | cend)), (uint_16) 0x3D5);
}

void IO::VGADisplay::enableCursor() {
	IO::VGADisplay::enableCursor(12, 15);
}

void IO::VGADisplay::setCursorPosition(uint_16 x, uint_16 y) {
	IO::VGADisplay::currentX = x; IO::VGADisplay::currentY = y;

	uint_16 cloc = (y * (uint_16) IO::VGADisplay::sizeX) + x;
	IO::Port::out((uint_8) 0x0E, (uint_16) 0x03D4);
	IO::Port::out((uint_8) ((cloc >> 8) & 0xFF), (uint_16) 0x03D5);
	IO::Port::out((uint_8) 0x0F, (uint_16) 0x03D4);
	IO::Port::out((uint_8) (cloc & 0xFF), (uint_16) 0x03D5);
}

void IO::VGADisplay::getCursorPosition(uint_16 *x, uint_16 *y) {
	*x = IO::VGADisplay::currentX; *y = IO::VGADisplay::currentY;
}

void IO::VGADisplay::scroll(int c, bool scr) {
	uint_16 *vmem = (uint_16 *) V_MEMORY_ADDRESS;

	for (int i = 0; i < c; i++) {
		for (int p = 0; p <= IO::VGADisplay::sizeX * (IO::VGADisplay::sizeY - 1); p++)
			vmem[p] = vmem[p + IO::VGADisplay::sizeX];

		for (int p = IO::VGADisplay::sizeX * (IO::VGADisplay::sizeY - 1); p < IO::VGADisplay::sizeX * (IO::VGADisplay::sizeY); p++)
			vmem[p] = IO::VGADisplay::newCharacter(' ', 0x7, 0x0);

		if (IO::VGADisplay::currentY > 0 && scr)
			IO::VGADisplay::setCursorPosition(IO::VGADisplay::currentX, IO::VGADisplay::currentY - 1);
	}

}

void IO::VGADisplay::scroll(int c) {
	IO::VGADisplay::scroll(c, true);	
}

void IO::VGADisplay::clear() {
	uint_16 *video_memory = (uint_16*) V_MEMORY_ADDRESS;

	for (int p = 0; p < (IO::VGADisplay::sizeX - 1) * IO::VGADisplay::sizeY; p++)
		video_memory[p] = IO::VGADisplay::newCharacter(' ', 0x7, 0x0);
}

void IO::VGADisplay::put(char c, uint_8 fg, uint_8 bg, int x, int y) {
	uint_16 *video_memory = (uint_16*) V_MEMORY_ADDRESS;
	video_memory[y * IO::VGADisplay::sizeX + x] = IO::VGADisplay::newCharacter(c, fg, bg);
}

void IO::VGADisplay::put(char c, uint_8 fg, uint_8 bg, bool m) {
	switch (c) {
		case '\n':
			if (IO::VGADisplay::currentY >= IO::VGADisplay::sizeY) 
				IO::VGADisplay::scroll(IO::VGADisplay::currentY - (IO::VGADisplay::sizeY - 1));
			if (m)
				IO::VGADisplay::currentY++;
			[[fallthrough]];
		case '\r':
			if (m)
				IO::VGADisplay::currentX = 0;
			if (IO::VGADisplay::currentX >= IO::VGADisplay::sizeX - 1) {
				if (IO::VGADisplay::currentY >= IO::VGADisplay::sizeY - 1)
					IO::VGADisplay::scroll(IO::VGADisplay::currentY - (IO::VGADisplay::sizeY - 1));
				else
					IO::VGADisplay::currentY++;
				IO::VGADisplay::currentX = 0;
			}
			break;
		default:
			IO::VGADisplay::put(c, fg, bg, IO::VGADisplay::currentX, IO::VGADisplay::currentY);
			break;
	}

	if (m && !(c == '\n' || c == '\r')) {
		if (IO::VGADisplay::currentX >= IO::VGADisplay::sizeX - 1) {
			if (IO::VGADisplay::currentY >= IO::VGADisplay::sizeY - 1)
				IO::VGADisplay::scroll(IO::VGADisplay::currentY - (IO::VGADisplay::sizeY - 1));
			else
				IO::VGADisplay::currentY++;
			IO::VGADisplay::currentX = 0;
		} else
			IO::VGADisplay::currentX++;
	}

	IO::VGADisplay::setCursorPosition(IO::VGADisplay::currentX, IO::VGADisplay::currentY);
}

void IO::VGADisplay::put(char c, uint_8 fg, uint_8 bg) {
	IO::VGADisplay::put(c, fg, bg, true);
}

void IO::VGADisplay::putString(const char *c, uint_8 fg, uint_8 bg) {
	int slen = String::length(c);

	uint_16 tx = currentX;
	uint_16 ty = currentY;

	for (int i = 0; i < slen; i++) {
		switch (c[i]) {
			case '\n':
				if (ty >= IO::VGADisplay::sizeY - 1) {
					IO::VGADisplay::scroll(1);
				} else
					ty++;
				[[fallthrough]];
			case '\r':
				tx = 0;
				break;
			default:
				IO::VGADisplay::put(c[i], fg, bg, tx, ty);
				break;
		}

		if (c[i] == '\n' || c[i] == '\r')
			continue;
		else {
			if (tx >= IO::VGADisplay::sizeX - 1) {
				if (ty >= IO::VGADisplay::sizeY - 1)
					IO::VGADisplay::scroll(1);
				else
					ty++;
				tx = 0;
			} else
				tx++;
		}
	}

	IO::VGADisplay::setCursorPosition(tx, ty);
}

void IO::VGADisplay::putBoolean(bool *c, uint_8 fg, uint_8 bg) {
	if (c)
		IO::VGADisplay::putString("true", fg, bg);
	else
		IO::VGADisplay::putString("false", fg, bg);
}

void IO::VGADisplay::putInteger(int n, int base, uint_8 fg, uint_8 bg) {
	char numb[34];
	String::itoa(numb, n, base);
	IO::VGADisplay::putString(numb, fg, bg);
}

void IO::VGADisplay::putInteger(uint_32 n, int b, uint_8 fg, uint_8 bg) {
	char numb[33];
	String::itoa(numb, n, b);
	IO::VGADisplay::putString(numb, fg, bg);
}

void IO::VGADisplay::putInteger(uint_16 n, int b, uint_8 fg, uint_8 bg) {
	char numb[17];
	String::itoa(numb, n, b);
	IO::VGADisplay::putString(numb, fg, bg);
}

void IO::VGADisplay::putInteger(uint_8 n, int b, uint_8 fg, uint_8 bg) {
	char numb[9];
	String::itoa(numb, n, b);
	IO::VGADisplay::putString(numb, fg, bg);
}