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
#ifndef IO_H							// We define the I/O header
#define IO_H

#include "../common/common.hpp" 		// We want to use common ports

namespace IO {
	class Port {
	private:
		uint_16 port;

	public:
		static void out(uint_8 val, uint_16 port);						// Outputs a byte to the specified port
		static void out(uint_16 val, uint_16 port);						// Outputs a word to the specified port
		static void out(uint_32 val, uint_16 port);						// Outputs a dword to the specified port

		static void in(uint_16 port, uint_8 *res);						// Inputs a byte from the specified port
		static void in(uint_16 port, uint_16 *res);						// Inputs a word from the specified port
		static void in(uint_16 port, uint_32 *res);						// Inputs a dword to the specified port
		
		Port(uint_16 port);												// Constructor for class
		void out(uint_8 val);											// Outputs a byte with the object
		void out(uint_16 val);											// Outputs a word with the object
		void out(uint_32 val);											// Outputs a dword with the object

		void in(uint_8 *res);											// Inputs a byte with the object
		void in(uint_16 *res);											// Inputs a word with the object
		void in(uint_32 *res);											// Inputs a dword with the object
	};
};

#endif