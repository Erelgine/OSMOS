/*
 * The String header, for string manipulations
 * for more details.
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

#ifndef STRING_H
#define STRING_H

#include "common.hpp" // We use unsigned integers

class String {
private:
	static const char default_dmap[];											// The default digit map, see string.cpp

public:
	static int length(const char *str);											// Counts the number of characters of a string until \0
	static void empty(char *str, int size);										// Clears a string with size
	static int compare(const char *dst, const char *source, int c);				// Compares a string with another until c
	static int compare(const char *dst, const char *src);						// Compares a string with another until \0
	static void copy(char *dst, const char *src, int len);						// Copies a string from src to dst until maxlen
	static void copy(char *dst, const char *src);								// Copies a string from src to dst
	static void concatenate(char *dst, const char *src);						// Concatenates dst with src
	static void flip(char *str, int count);										// Flips a string count times 
	static void flip(char *str);												// Flips a string
	static int count(char *str, char *chars);									// Counts how many specified characters are present in str

	static void itoa(char *str, int num, int base, const char *dmap);			// Transforms a number into a char array
	static void itoa(char *str, uint_32 num, int base, const char *dmap);		// Transforms a unsigned number into a char array
	static void itoa(char *str, int num, int base);								// Same, without dmap
	static void itoa(char *str, uint_32 num, int base);							// Same, without dmap
};

#endif