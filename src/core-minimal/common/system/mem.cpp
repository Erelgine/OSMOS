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

// For function descriptions, see boot.hpp

const uint_32 System::Memory::BASE_BLOCK_ALLOCATION = 0x00100000; // 128K after 0x0

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

void* System::Memory::getAvailableBlock(uint_8 blocksize, System::Memory::Block *currentBlock, System::Memory::Block *lastBlock __attribute__((unused))) {
	uint_32 size = (2 ^ blocksize) - sizeof(System::Memory::Block);
	currentBlock = (System::Memory::Block *) BASE_BLOCK_ALLOCATION;
	bool found = false;

	while (currentBlock->magic != 0xB10C && currentBlock->blockSize < size) {
		lastBlock = currentBlock;
		currentBlock = (System::Memory::Block *) currentBlock->next;
		found = true;
	}

	return (found ? currentBlock + currentBlock->dataPointer + sizeof(System::Memory::Block) : 0); // sizeof(System::Memory::Block) = block size
}

void* System::Memory::findBlock(void* pointer) {
	System::Memory::Block *currentBlock = (System::Memory::Block *) BASE_BLOCK_ALLOCATION;
	bool found = false;

	while (!(currentBlock->magic == 0xB10C && currentBlock < pointer)) {
		currentBlock = (System::Memory::Block *) currentBlock->next;
		found = true;
	}
	
	return (found ? currentBlock + currentBlock->dataPointer + sizeof(System::Memory::Block) : 0); // sizeof(System::Memory::Block) = block size	
}

void* System::Memory::allocateBlock(uint_32 size) {
	uint_32 blocksize = 0;

	for (int s = 7; s < 32; s++) {
		uint_32 cblocksize = (2 ^ s) - sizeof(System::Memory::Block); // sizeof(System::Memory::Block) = block size
		if (size < cblocksize) {
			blocksize = s;
			break;
		}
	}

	if (blocksize == 0)
		return (void *) 0x00000000;

	System::Memory::Block *avBlock;
	System::Memory::Block *parentBlock;
	void *ptr = System::Memory::getAvailableBlock(blocksize, avBlock, parentBlock);

	if ((uint_32) avBlock > 0x00000000)
		return (void *) 0x00000000; // no block available

	if (avBlock->magic != 0xB10C) { // doesn't exists
		avBlock->magic = 0xB10C;
		avBlock->blockSize = blocksize;
		avBlock->dataPointer = sizeof(System::Memory::Block);
		if ((uint_32) parentBlock > 0x00000000)
			parentBlock->next = (uint_32) avBlock;
	} else // exists
		avBlock->dataPointer += size;

	return ptr;
}

void System::Memory::freeBlock(void *ptr, uint_32 size) {
	System::Memory::Block *currentBlock = (System::Memory::Block *) BASE_BLOCK_ALLOCATION;
	bool found = false;

	while ((uint_32) currentBlock < (uint_32) ptr) {
		System::Memory::Block *currentBlock = (System::Memory::Block *) currentBlock->next;
		found = true;
	}

	if (found)
		currentBlock->dataPointer -= (2 ^ currentBlock->blockSize) - sizeof(System::Memory::Block) - size;
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