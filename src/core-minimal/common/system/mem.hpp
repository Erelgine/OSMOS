/*
 * The Memory header, for memory manipulation
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

#ifndef MEM_H
#define MEM_H

#include "../../boot.hpp"

namespace System {
	class Memory {
	public:
		struct Block {
			uint_16 magic;
			uint_8 blockSize;
			uint_32 dataPointer;
			uint_32 next;
		} __attribute__((packed));

		static const uint_32 BASE_BLOCK_ALLOCATION;

		static void set(uint_8 *dst, uint_8 val, int size);								// Fills the memory from beg -> beg + size with val
		static void set(uint_16 *dst, uint_16 val, int size);							// Same, but with 16-bit size
		static void set(uint_32 *dst, uint_32 val, int size);							// Same, but with 32-bit size
		static void copy(char *dst, char *src, int size);								// Copies the memory from beg -> beg + size with src
		static void* findAvailableBlock(uint_8 blocksize, System::Memory::Block *block, System::Memory::Block *parentBlock);
		static void* findBlock(void *pointer);
		static void* allocateBlock(uint_32 size);
		static void freeBlock(void *ptr, uint_32 size);
	};
};

// new and delete keywords implementation

void* operator new(uint_32 size);
void* operator new[](uint_32 size);
void operator delete(void *ptr);
void operator delete[](void *ptr);
void operator delete(void *ptr, uint_32 size);
void operator delete[](void *ptr, uint_32 size);

#endif