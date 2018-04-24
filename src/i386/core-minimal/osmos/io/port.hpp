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

#ifndef PORT_HPP
#define PORT_HPP

#include "../osmos.hpp"

namespace OSMOS {
	namespace IO {
		class Port {
		public:
			static void in(uint16_t port, uint8_t *value); /* Inputs a byte */
			static void in(uint16_t port, uint16_t *value); /* Inputs a word */
			static void in(uint16_t port, uint32_t *value); /* Inputs a dword */

			static void out(uint16_t port, uint8_t value); /* Outputs a byte */
			static void out(uint16_t port, uint16_t value); /* Outputs a word */
			static void out(uint16_t port, uint32_t value); /* Outputs a dword */
		};
	};
};

#endif