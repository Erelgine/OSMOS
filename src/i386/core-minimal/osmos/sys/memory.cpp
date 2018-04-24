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

uint8_t OSMOS::System::Memory::BLOCK_STATUS_FREE			= 0b00000000;
uint8_t OSMOS::System::Memory::BLOCK_STATUS_USED			= 0b00000001;
uint8_t OSMOS::System::Memory::BLOCK_STATUS_RESERVED		= 0b00000010;
uint8_t OSMOS::System::Memory::BLOCK_TYPE_INVALID			= 0b00000000;
uint8_t OSMOS::System::Memory::BLOCK_TYPE_DATA				= 0b00000100;
uint8_t OSMOS::System::Memory::BLOCK_TYPE_CLASS				= 0b00001000;
uint8_t OSMOS::System::Memory::BLOCK_TYPE_CODE				= 0b00001100;

void OSMOS::System::Memory::fill(uint8_t *ptr, uint32_t count, uint8_t val) {
	for (uint32_t i = 0; i < count; i++)
		ptr[i] = val;
}

void OSMOS::System::Memory::fill(uint16_t *ptr, uint32_t count, uint16_t val) {
	for (uint32_t i = 0; i < count; i++)
		ptr[i] = val;	
}

void OSMOS::System::Memory::fill(uint32_t *ptr, uint32_t count, uint32_t val) {
	for (uint32_t i = 0; i < count; i++)
		ptr[i] = val;
}

void OSMOS::System::Memory::fill(uint64_t *ptr, uint32_t count, uint64_t val) {
	for (uint32_t i = 0; i < count; i++)
		ptr[i] = val;	
}

void OSMOS::System::Memory::copy(uint8_t *target, uint8_t *source, uint32_t count) {
	for (uint32_t i = 0; i < count; i++)
		target[i] = source[i];
}

void OSMOS::System::Memory::copy(uint16_t *target, uint16_t *source, uint32_t count) {
	for (uint32_t i = 0; i < count; i++)
		target[i] = source[i];
}

void OSMOS::System::Memory::copy(uint32_t *target, uint32_t *source, uint32_t count) {
	for (uint32_t i = 0; i < count; i++)
		target[i] = source[i];
}

void OSMOS::System::Memory::copy(uint64_t *target, uint64_t *source, uint32_t count) {
	for (uint32_t i = 0; i < count; i++)
		target[i] = source[i];
}
