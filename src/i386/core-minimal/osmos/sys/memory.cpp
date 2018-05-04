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

#include "memory.hpp"

#include <stddef.h>
#include "../osmos.hpp"

size_t OSMOS::System::Memory::BLOCK_BASE_ADDRESS         = 0;
size_t OSMOS::System::Memory::BLOCK_LIMIT_ADDRESS        = 0;

uint16_t OSMOS::System::Memory::BLOCK_MAGIC_VALUE           = 0xB6A0;

uint8_t OSMOS::System::Memory::BLOCK_STATUS_USED            = 0b0001;
uint8_t OSMOS::System::Memory::BLOCK_STATUS_RESERVED        = 0b0010;

uint8_t OSMOS::System::Memory::BLOCK_TYPE_DATA              = 0b0100;
uint8_t OSMOS::System::Memory::BLOCK_TYPE_CODE              = 0b1000;

void OSMOS::System::Memory::fill(uint8_t *ptr, size_t size, uint8_t val) {
    for (size_t i = 0; i < size; i++)
        ptr[i] = val;
}

void OSMOS::System::Memory::fill(uint16_t *ptr, size_t size, uint16_t val) {
    for (size_t i = 0; i < size; i += 2)
        ptr[i] = val;
}

void OSMOS::System::Memory::fill(uint32_t *ptr, size_t size, uint32_t val) {
    for (size_t i = 0; i < size; i += 4)
        ptr[i] = val;
}

void OSMOS::System::Memory::fill(uint64_t *ptr, size_t size, uint64_t val) {
    for (size_t i = 0; i < size; i += 8)
        ptr[i] = val;
}

void OSMOS::System::Memory::copy(uint8_t *target, uint8_t *source, size_t size) {
    for (size_t i = 0; i < size; i++)
        target[i] = source[i];
}

void OSMOS::System::Memory::copy(uint16_t *target, uint16_t *source, size_t size) {
    for (size_t i = 0; i < size; i++)
        target[i] = source[i];
}

void OSMOS::System::Memory::copy(uint32_t *target, uint32_t *source, size_t size) {
    for (size_t i = 0; i < size; i++)
        target[i] = source[i];
}

void OSMOS::System::Memory::copy(uint64_t *target, uint64_t *source, size_t size) {
    for (size_t i = 0; i < size; i++)
        target[i] = source[i];
}

void OSMOS::System::Memory::setBaseAddress(size_t address) {
    if (address != NULL)
        OSMOS::System::Memory::BLOCK_BASE_ADDRESS = address;
}

void OSMOS::System::Memory::setLimitAddress(size_t address) {
    if (address != NULL)
        OSMOS::System::Memory::BLOCK_LIMIT_ADDRESS = address;
}

size_t OSMOS::System::Memory::getBaseAddress() {
    return OSMOS::System::Memory::BLOCK_BASE_ADDRESS;
}

size_t OSMOS::System::Memory::getLimitAddress() {
    return OSMOS::System::Memory::BLOCK_LIMIT_ADDRESS;
}

bool OSMOS::System::Memory::isValid(OSMOS::System::Memory::Block* block) {
    return block->magic == OSMOS::System::Memory::BLOCK_MAGIC_VALUE;
}

bool OSMOS::System::Memory::isAllocated(OSMOS::System::Memory::Block *block) {
    return OSMOS::System::Memory::isValid(block) && (block->flags & OSMOS::System::Memory::BLOCK_STATUS_USED);
}

bool OSMOS::System::Memory::isReserved(OSMOS::System::Memory::Block *block) {
    return OSMOS::System::Memory::isValid(block) && (block->flags & OSMOS::System::Memory::BLOCK_STATUS_RESERVED);
}

bool OSMOS::System::Memory::isData(OSMOS::System::Memory::Block *block) {
    return OSMOS::System::Memory::isValid(block) && (block->flags & OSMOS::System::Memory::BLOCK_TYPE_DATA);
}

bool OSMOS::System::Memory::isCode(OSMOS::System::Memory::Block *block) {
    return OSMOS::System::Memory::isValid(block) && (block->flags & OSMOS::System::Memory::BLOCK_TYPE_CODE);
}

uint64_t OSMOS::System::Memory::getBlockSize(OSMOS::System::Memory::Block *block) {
    return (OSMOS::System::Memory::isAllocated(block) ? 2 ^ (block->size + 6) : NULL);
}

uint64_t OSMOS::System::Memory::getSize(OSMOS::System::Memory::Block *block) {
    return OSMOS::System::Memory::getBlockSize(block) - sizeof(OSMOS::System::Memory::Block);
}

size_t OSMOS::System::Memory::findAvailableBlock(size_t start, uint64_t size) {
    OSMOS::System::Memory::Block* aBlock = (OSMOS::System::Memory::Block *) start;
    bool found = false;

    if (size == 0 || start > OSMOS::System::Memory::BLOCK_LIMIT_ADDRESS || size > OSMOS::System::Memory::BLOCK_LIMIT_ADDRESS - OSMOS::System::Memory::BLOCK_BASE_ADDRESS)
        return NULL;

    uint64_t aSize;
    for (size_t address = start; address < OSMOS::System::Memory::BLOCK_LIMIT_ADDRESS; address += aSize) {
        aBlock = (OSMOS::System::Memory::Block *) address;
        aSize = OSMOS::System::Memory::getBlockSize(aBlock);
        
        if (!OSMOS::System::Memory::isAllocated(aBlock)) {
            size_t nbAddress = OSMOS::System::Memory::findAllocatedBlock(address);
            OSMOS::System::Memory::Block *nextBlock = (OSMOS::System::Memory::Block *) (nbAddress != NULL ? nbAddress : address);
            
            if (OSMOS::System::Memory::isAllocated(nextBlock)) {
                if (nbAddress != NULL && nbAddress - address < size)
                    continue;
            }

            found = true;
            break;
        }

        address += size;
    }
    
    return (size_t) (found ? aBlock : NULL);
}

size_t OSMOS::System::Memory::findAvailableBlock(uint64_t size) {
    return OSMOS::System::Memory::findAvailableBlock(OSMOS::System::Memory::BLOCK_BASE_ADDRESS, size);
}

size_t OSMOS::System::Memory::findAllocatedBlock(size_t start) {
    OSMOS::System::Memory::Block *currentBlock = (OSMOS::System::Memory::Block *) start;
    bool found = false;

    uint64_t size = 0;
    for (size_t address = start; address < OSMOS::System::Memory::BLOCK_LIMIT_ADDRESS; address += size) {
        currentBlock = (OSMOS::System::Memory::Block *) address;
        size = OSMOS::System::Memory::getBlockSize(currentBlock);

        if (size != NULL) {
            found = true;
            break;
        } else
            size = 2 ^ 6;
    }

    return (size_t) (found ? currentBlock : NULL);
}

size_t OSMOS::System::Memory::findBlock(size_t pointer) {
    if (pointer < OSMOS::System::Memory::BLOCK_BASE_ADDRESS || pointer > OSMOS::System::Memory::BLOCK_LIMIT_ADDRESS)
        return NULL;
    
    OSMOS::System::Memory::Block *currentBlock;

    uint64_t size = 0;
    for (size_t address = OSMOS::System::Memory::BLOCK_BASE_ADDRESS; address < OSMOS::System::Memory::BLOCK_LIMIT_ADDRESS; address += size) {
        currentBlock = (OSMOS::System::Memory::Block *) address;
        size = 2 ^ 6;

        if (OSMOS::System::Memory::isValid(currentBlock)) {
            size = OSMOS::System::Memory::getBlockSize(currentBlock);
            if (size != NULL && OSMOS::System::Memory::isAllocated(currentBlock) && address + OSMOS::System::Memory::getBlockSize(currentBlock) > pointer && address < pointer)
                return (size_t) currentBlock;
        }
    }

    return NULL;
}

size_t OSMOS::System::Memory::allocateBlock(size_t size, uint8_t flags) {
    size_t blockAddress = OSMOS::System::Memory::findAvailableBlock(size);

    if (blockAddress == NULL)
        return NULL;

    OSMOS::System::Memory::Block *block = (OSMOS::System::Memory::Block *) blockAddress;
    block->magic = OSMOS::System::Memory::BLOCK_MAGIC_VALUE;
    block->flags = (flags & 0b1110) | OSMOS::System::Memory::BLOCK_STATUS_USED;
    uint8_t cSize = 0;
    for (; cSize < 32; cSize++)
        if (size < (uint64_t) (2 ^ (cSize + 6)))
            break;
    block->size = cSize;

    return blockAddress + sizeof(OSMOS::System::Memory::Block);
}

size_t OSMOS::System::Memory::allocateBlock(size_t size) {
    return OSMOS::System::Memory::allocateBlock(size, OSMOS::System::Memory::BLOCK_TYPE_DATA);
}

void OSMOS::System::Memory::freeBlock(OSMOS::System::Memory::Block *block) {
    if (block->flags & OSMOS::System::Memory::BLOCK_STATUS_RESERVED)
        return;
    
    block->flags |= OSMOS::System::Memory::BLOCK_STATUS_USED;
}

void OSMOS::System::Memory::freeBlock(size_t pointer) {
    size_t blockb = OSMOS::System::Memory::findBlock(pointer);

    if (blockb == NULL)
        return;
    
    OSMOS::System::Memory::freeBlock(blockb);
}

void *operator new(size_t size) {
    return (void *) OSMOS::System::Memory::allocateBlock(size, OSMOS::System::Memory::BLOCK_TYPE_CODE);
}

void *operator new[](size_t size) {
    return (void *) OSMOS::System::Memory::allocateBlock(size, OSMOS::System::Memory::BLOCK_TYPE_DATA);
}

void operator delete(void *pointer) {
    OSMOS::System::Memory::freeBlock((size_t) pointer);
}

void operator delete[](void *pointer) {
    OSMOS::System::Memory::freeBlock((size_t) pointer);
}

void operator delete(void *pointer, size_t size) {
    size_t ablocka = OSMOS::System::Memory::findBlock((size_t) pointer);
    if (ablocka == NULL)
        return;
    OSMOS::System::Memory::Block *ablock = (OSMOS::System::Memory::Block *) ablocka;
    uint64_t ablocksize = OSMOS::System::Memory::getSize(ablock);
    if (ablocksize != size)
        OSMOS::System::Memory::fill((uint8_t *) pointer, size, NULL);
    else
        OSMOS::System::Memory::freeBlock((size_t) pointer);
}

void operator delete[](void *pointer, size_t size) {
    operator delete(pointer, size);
}