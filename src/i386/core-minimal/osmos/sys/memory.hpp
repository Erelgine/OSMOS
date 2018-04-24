/*
 * The memory allocation class
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

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "../osmos.hpp"

namespace OSMOS {
	namespace System {
		class Memory {
		public:
			// The flags for the memory block
			static uint8_t BLOCK_STATUS_FREE; // A free block that can be allocated
			static uint8_t BLOCK_STATUS_USED; // A used block that cannot be allocated
			static uint8_t BLOCK_STATUS_RESERVED; // A reserved block that is used by the kernel
			static uint8_t BLOCK_TYPE_INVALID; // A invalid block that should be reallocated
			static uint8_t BLOCK_TYPE_DATA; // A data block that should contain values such as a structure
			static uint8_t BLOCK_TYPE_CLASS; // A class block that should contain a class
			static uint8_t BLOCK_TYPE_CODE; // A code block that contains machine code

			// The memory block
			struct Block {
				uint8_t flags:4; // The flags of the block (4-bit wide)
				uint8_t next; // The next block that comes after this one
				uint8_t size; // The maximum size the block can handle (2 ^ (b + 6) - sizeof(<memory block>))
				uint32_t free; // The number of bytes remaining in the block (size - used)
			} __attribute__((packed));

			static void fill(uint8_t *ptr, uint32_t count, uint8_t val); // Fills from ptr to ptr+count with a byte wide val
			static void fill(uint16_t *ptr, uint32_t count, uint16_t val); // Fills from ptr to ptr+count with a word wide val
			static void fill(uint32_t *ptr, uint32_t count, uint32_t val); // Fills from ptr to ptr+count with a dword wide val
			static void fill(uint64_t *ptr, uint32_t count, uint64_t val); // Fills from ptr to ptr+count with a qword wide val

			static void copy(uint8_t *target, uint8_t *source, uint32_t count); // Copies from ptr to ptr+count with a byte wide val
			static void copy(uint16_t *target, uint16_t *source, uint32_t count); // Copies from ptr to ptr+count with a word wide val
			static void copy(uint32_t *target, uint32_t *source, uint32_t count); // Copies from ptr to ptr+count with a dword wide val
			static void copy(uint64_t *target, uint64_t *source, uint32_t count); // Copies from ptr to ptr+count with a qword wide val
		};
	};
};

#endif