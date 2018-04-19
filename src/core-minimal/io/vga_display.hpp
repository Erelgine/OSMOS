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
#ifndef VGA_DISPLAY_H				// We define the VGA display header
#define VGA_DISPLAY_H

#include "io.hpp"					// We use the I/O interaction (in order to control the cursor)
#include "../common/string.hpp"		// We use strings (in order to count the length of a string)
#include "../common/common.hpp"		// We use the common objects (such as a boolean)
#include "../common/system/mem.hpp"	// We use memory manipulation (for screen scrolling)

// We define the VGADisplay class inside the IO namespace
namespace IO {
	class VGADisplay {
	private:
		static uint_16 currentX, currentY;	// Here is variables for saving the position of the cursor
		static uint_16 sizeX, sizeY;		// ...and size of the screen

	public:
		static uint_16 newCharacter(char c, uint_8 fg, uint_8 bg);		// Creates a new character for the video memory

		static void disableCursor();									// Disables the cursor
		static void enableCursor(uint_8 cstart, uint_8 cend);			// Enables the cursor with scanline values
		static void enableCursor();										// Enables the cursor with predefined scaline values
		static void setCursorPosition(uint_16 x, uint_16 y);			// Sets the cursor position
		static void getCursorPosition(uint_16 *x, uint_16 *y);			// Gets the cursor position
		static void scroll(int c, bool scr);							// Scrolls the screen (if scr == 1, updates the cursor position)
		static void scroll(int c);										// Scrolls the screen
		static void clear();											// Clears the screen
		
		static void put(char c, uint_8 bg, uint_8 fg, int x, int y);	// Puts a character on the screen on X, Y
		static void put(char c, uint_8 bg, uint_8 fg, bool m);			// Puts a character at the current position of the cursor, and move if m == 1
		static void put(char c, uint_8 bg, uint_8 fg);					// Puts a character on the screen
		static void putString(const char *s, uint_8 bg, uint_8 fg);		// Puts a string on the screen at the current position of the cursor
		static void putBoolean(bool *b, uint_8 bg, uint_8 fg);			// Puts the string representation of a boolean at the current position of the cursor
		static void putInteger(int n, int base, uint_8 fg, uint_8 bg);	// Puts the string representation of a number at the current position of the cursor
		static void putInteger(uint_32 n, int b, uint_8 fg, uint_8 bg);	// Puts the string representation of a unsigned 32-bit integer at the current position of the cursor
		static void putInteger(uint_16 n, int b, uint_8 fg, uint_8 bg);	// Puts the string representation of a unsigned 16-bit integer at the current position of the cursor
		static void putInteger(uint_8 n, int b, uint_8 fg, uint_8 bg);	// Puts the string representation of a unsigned 8-bit integer at the current position of the cursor
	};
};

#endif