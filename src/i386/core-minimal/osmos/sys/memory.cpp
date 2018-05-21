/**
 * @file core-minimal/osmos/sys/memory.cpp
 * @brief The main code for the Memory class
 **/

/*
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

size_t OSMOS::System::Memory::Management::Area::LOWER_ADDRESS           = 0x00100000;
size_t OSMOS::System::Memory::Management::Area::UPPER_ADDRESS           = 0x00EFFFFF;

const uint16_t OSMOS::System::Memory::Management::BLOCK_MAGIC_VALUE     = 0xF8F7;

void OSMOS::System::Memory::Access::fill(void *ptr, size_t size, uint8_t val) {
    uint8_t *cptr = (uint8_t *) ptr;
    for (size_t i = 0; i < size; i++)
        cptr[i] = val;
}

void OSMOS::System::Memory::Access::copy(void *target, void *source, size_t size) {
    uint8_t *ctarget = (uint8_t*) target;
    uint8_t *csource = (uint8_t *) source;
    for (size_t i = 0; i < size; i++)
        ctarget[i] = csource[i];
}

void OSMOS::System::Memory::Management::Area::getArea(size_t *lowerAddress, size_t *upperAddress) {
    *lowerAddress = OSMOS::System::Memory::Management::Area::LOWER_ADDRESS;
    *upperAddress = OSMOS::System::Memory::Management::Area::UPPER_ADDRESS;
}

void OSMOS::System::Memory::Management::Area::setArea(size_t lowerAddress, size_t upperAddress) {
    if (upperAddress < lowerAddress || OSMOS::System::Memory::Management::Area::getAllocatedSize() > (upperAddress - lowerAddress))
        return;

    OSMOS::System::Memory::Management::Area::LOWER_ADDRESS = lowerAddress;
    OSMOS::System::Memory::Management::Area::UPPER_ADDRESS = upperAddress;
}

uint64_t OSMOS::System::Memory::Management::Area::getAllocatedSize() {
    uint64_t size = 0;

    for (size_t address = OSMOS::System::Memory::Management::Area::LOWER_ADDRESS;
                address < OSMOS::System::Memory::Management::Area::UPPER_ADDRESS;
                address += sizeof(OSMOS::System::Memory::Management::Block) + 1)
        if (OSMOS::System::Memory::Management::isBlockAllocated((OSMOS::System::Memory::Management::Block *) address)) {
            OSMOS::System::Memory::Management::Block *block = (OSMOS::System::Memory::Management::Block *) address;
            size += block->size;
        }

    return size;
}

uint64_t OSMOS::System::Memory::Management::Area::getAllocatedCount() {
    uint64_t count = 0;

    for (size_t address = OSMOS::System::Memory::Management::Area::LOWER_ADDRESS;
                address < OSMOS::System::Memory::Management::Area::UPPER_ADDRESS;
                address += sizeof(OSMOS::System::Memory::Management::Block) + 1)
        if (OSMOS::System::Memory::Management::isBlockAllocated((OSMOS::System::Memory::Management::Block *) address))
            count++;

    return count;
}

bool OSMOS::System::Memory::Management::isBlockAllocated(OSMOS::System::Memory::Management::Block *block) {
    return (block->magic == OSMOS::System::Memory::Management::BLOCK_MAGIC_VALUE) && block->isAllocated;
}

size_t OSMOS::System::Memory::Management::findBlock(size_t startAddress, bool allocated, uint64_t size) {
    size_t lowerAddress, upperAddress = 0;
    OSMOS::System::Memory::Management::Area::getArea(&lowerAddress, &upperAddress);

    for (size_t address = startAddress; address < upperAddress;
        address += sizeof(OSMOS::System::Memory::Management::Block) + 1) {
        OSMOS::System::Memory::Management::Block *block = (OSMOS::System::Memory::Management::Block *) address;
        if (allocated && OSMOS::System::Memory::Management::isBlockAllocated(block) && size == NULL)
            return address;
        else if (!allocated && !OSMOS::System::Memory::Management::isBlockAllocated(block)) {
            size_t nBlock = OSMOS::System::Memory::Management::findBlock(address, true);
            if (nBlock == NULL || nBlock - address > size + sizeof(OSMOS::System::Memory::Management::Block) + 1)
                return address;
        }
    }

    return NULL;
}

size_t OSMOS::System::Memory::Management::findBlock(size_t startAddress, bool allocated) {
    return OSMOS::System::Memory::Management::findBlock(startAddress, allocated, NULL);
}

size_t OSMOS::System::Memory::Management::allocateBlock(uint64_t size) {
    if (size < 1)
        return NULL;

    size_t lowerAddress, upperAddress = 0;
    OSMOS::System::Memory::Management::Area::getArea(&lowerAddress, &upperAddress);

    size_t blockAddress = OSMOS::System::Memory::Management::findBlock(lowerAddress, false, size);
    if (blockAddress == NULL)
        return NULL;

    OSMOS::System::Memory::Management::Block *block = (OSMOS::System::Memory::Management::Block *) blockAddress;
    block->magic = OSMOS::System::Memory::Management::BLOCK_MAGIC_VALUE;
    block->isAllocated = true;
    block->size = size;

    return blockAddress + sizeof(OSMOS::System::Memory::Management::Block);
}

bool OSMOS::System::Memory::Management::deallocateBlock(size_t address, uint64_t size) {
    size_t lowerAddress, upperAddress = 0;
    OSMOS::System::Memory::Management::Area::getArea(&lowerAddress, &upperAddress);

    if (address < lowerAddress || address > upperAddress)
        return false;

    size_t blockAddress = address;
    if (!OSMOS::System::Memory::Management::isBlockAllocated((OSMOS::System::Memory::Management::Block *) address)) {
        if (!OSMOS::System::Memory::Management::isBlockAllocated((OSMOS::System::Memory::Management::Block *) address - sizeof(OSMOS::System::Memory::Management::Block)))
            return false;
        else
            blockAddress -= sizeof(OSMOS::System::Memory::Management::Block);
    }

    OSMOS::System::Memory::Access::fill((uint8_t *) blockAddress, size, NULL);

    return true;
}

void *operator new(size_t size) {
    return (void *) OSMOS::System::Memory::Management::allocateBlock(size);
}

void *operator new[](size_t size) {
    return (void *) OSMOS::System::Memory::Management::allocateBlock(size);
}

void operator delete(void *pointer) {
    OSMOS::System::Memory::Management::deallocateBlock((size_t) pointer, NULL);
}

void operator delete[](void *pointer) {
    OSMOS::System::Memory::Management::deallocateBlock((size_t) pointer, NULL);
}

void operator delete(void *pointer, size_t size) {
    OSMOS::System::Memory::Management::deallocateBlock((size_t) pointer, size);
}

void operator delete[](void *pointer, size_t size) {
    OSMOS::System::Memory::Management::deallocateBlock((size_t) pointer, size);
}