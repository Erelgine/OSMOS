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

#include "mem.hpp"

#include "../../boot.hpp"
#include "../../io/vga_display.hpp" // DEBUG

// For function descriptions, see boot.hpp

const uint_32 System::Memory::BASE_BLOCK_ALLOCATION = 0x001FFFFF; // 128K after 0x0

void System::Memory::set(uint_8 *trg, uint_8 val, int size) {
	for (int i = 0; i < size; i++)
		trg[i] = val;
}

void System::Memory::set(uint_16 *trg, uint_16 val, int size) {
	for (int i = 0; i < size; i++)
		trg[i] = val;	
}

void System::Memory::set(uint_32 *trg, uint_32 val, int size) {
	for (int i = 0; i < size; i++)
		trg[i] = val;	
}

void System::Memory::copy(char *trg, char *src, int size) {
	for (int i = 0; i < size; i++)
		trg[i] = src[i];
}

void* System::Memory::findAvailableBlock(uint_8 blocksize, System::Memory::Block *currentBlock, System::Memory::Block *lastBlock __attribute__((unused))) {
	// TODO: Write code for function
}

void* System::Memory::findBlock(void *pointer) {
	// TODO: Write code for function
}

void* System::Memory::allocateBlock(uint_32 size) {
	// TODO: Write code for function
}

void System::Memory::freeBlock(void *ptr, uint_32 size) {
	// TODO: Write code for function
}

void* operator new(uint_32 size)
{
	return System::Memory::allocateBlock(size);
}
 
void* operator new[](uint_32 size)
{
    return System::Memory::allocateBlock(size);
}
 
void operator delete(void *ptr)
{
	void *bpt = System::Memory::findBlock(ptr);
	if ((uint_32) bpt > 0) {
		System::Memory::Block *block = (System::Memory::Block *) bpt;
    	System::Memory::freeBlock(ptr, (2 ^ block->blockSize) - sizeof(System::Memory::Block) - (((uint_32) ptr) - ((uint_32) bpt)));
	}
}
 
void operator delete[](void *ptr)
{
    void *bpt = System::Memory::findBlock(ptr);
	if ((uint_32) bpt > 0) {
		System::Memory::Block *block = (System::Memory::Block *) bpt;
    	System::Memory::freeBlock(ptr, (2 ^ block->blockSize) - sizeof(System::Memory::Block) - (((uint_32) ptr) - ((uint_32) bpt)));
	}
}

void operator delete(void *ptr, uint_32 size)
{
    System::Memory::freeBlock(ptr, size);
}
 
void operator delete[](void *ptr, uint_32 size)
{
    System::Memory::freeBlock(ptr, size);
}