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

uint16_t OSMOS::System::Memory::BLOCK_MAGIC_VALUE           = 0xB6A0;

uint8_t OSMOS::System::Memory::BLOCK_STATUS_USED            = 0b0001;
uint8_t OSMOS::System::Memory::BLOCK_STATUS_RESERVED        = 0b0010;

uint8_t OSMOS::System::Memory::BLOCK_TYPE_DATA              = 0b0100;
uint8_t OSMOS::System::Memory::BLOCK_TYPE_CODE              = 0b1000;

void OSMOS::System::Memory::fill(uint8_t *ptr, address_t size, uint8_t val) {
    for (uint32_t i = 0; i < size; i++)
        ptr[i] = val;
}

void OSMOS::System::Memory::fill(uint16_t *ptr, address_t size, uint16_t val) {
    for (uint32_t i = 0; i < size; i++)
        ptr[i] = val;
}

void OSMOS::System::Memory::fill(uint32_t *ptr, address_t size, uint32_t val) {
    for (uint32_t i = 0; i < size; i++)
        ptr[i] = val;
}

void OSMOS::System::Memory::fill(uint64_t *ptr, address_t size, uint64_t val) {
    for (uint32_t i = 0; i < size; i++)
        ptr[i] = val;
}

void OSMOS::System::Memory::copy(uint8_t *target, uint8_t *source, address_t size) {
    for (uint32_t i = 0; i < size; i++)
        target[i] = source[i];
}

void OSMOS::System::Memory::copy(uint16_t *target, uint16_t *source, address_t size) {
    for (uint32_t i = 0; i < size; i++)
        target[i] = source[i];
}

void OSMOS::System::Memory::copy(uint32_t *target, uint32_t *source, address_t size) {
    for (uint32_t i = 0; i < size; i++)
        target[i] = source[i];
}

void OSMOS::System::Memory::copy(uint64_t *target, uint64_t *source, address_t size) {
    for (uint32_t i = 0; i < size; i++)
        target[i] = source[i];
}

bool OSMOS::System::Memory::isValid(OSMOS::System::Memory::Block* block) {
    return block->magic == OSMOS::System::Memory::BLOCK_MAGIC_VALUE || (block->flags | 0b1100) == 0;
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

uint64_t OSMOS::System::Memory::getSize(OSMOS::System::Memory::Block *block) {
    return 2 ^ (block->size + 6);
}