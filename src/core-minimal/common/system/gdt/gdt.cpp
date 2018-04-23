/*
 * The GDT class, necessary EVEN if GRUB provides us one.
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

#include "gdt.hpp"

#include "../../common.hpp"

#include "../../../io/vga_display.hpp" // DEBUG

const uint_8 System::GDT::ENTRY_FLAG_NONE						= 0b00000000;
const uint_8 System::GDT::ENTRY_FLAG_BIG_SIZE					= 0b01000000;
const uint_8 System::GDT::ENTRY_FLAG_GRANULARITY				= 0b10000000;

const uint_8 System::GDT::ACCESS_FLAG_NONE						= 0b00000000;
const uint_8 System::GDT::ACCESS_FLAG_ACCESSED					= 0b00000001;
const uint_8 System::GDT::ACCESS_FLAG_READ_WRITE				= 0b00000010;
const uint_8 System::GDT::ACCESS_FLAG_DIRECTION_CONFORMING		= 0b00000100;
const uint_8 System::GDT::ACCESS_FLAG_EXECUTABLE				= 0b00001000;
const uint_8 System::GDT::ACCESS_FLAG_REQUIRED					= 0b00010000;
const uint_8 System::GDT::ACCESS_FLAG_PRESENT					= 0b10000000;

const uint_8 System::GDT::ACCESS_PRIVILEGE_KERNEL_MODE 			= 0b00000000;
const uint_8 System::GDT::ACCESS_PRIVILEGE_ADMINISTRATIVE_MODE	= 0b00100000;
const uint_8 System::GDT::ACCESS_PRIVILEGE_MODERATIVE_MODE		= 0b01000000;
const uint_8 System::GDT::ACCESS_PRIVILEGE_USER_MODE			= 0b01100000;

void System::GDT::initializeEntry(uint_32 base, uint_32 limit, uint_8 access, uint_8 flags, struct System::GDT::Entry *gdt) {
	gdt->base_low			= base & 0xFFFF;
	gdt->base_middle		= (base >> 16) & 0xFF;
	gdt->base_high			= (base >> 24) & 0xFF;

	gdt->limit_low			= limit & 0xFFFF;
	gdt->limit_high_flags	= (limit >> 16) & 0x0F;
	gdt->limit_high_flags  |= flags & 0xF0;

	gdt->access				= access;
}

void System::GDT::setTable(struct System::GDT::Pointer *gdtr, struct System::GDT::Entry *gdt, uint_32 size) {
	gdtr->size = size;
	gdtr->base = (uint_32) gdt;

	asm("lgdt [%0]\n\t \
		 jmp 0x08:.segload\n\t \
		 .segload:\n\t \
		 mov ax, 0x10\n\t \
		 mov ds, ax\n\t \
		 mov es, ax\n\t \
		 mov fs, ax\n\t \
		 mov gs, ax\n\t \
		 mov ss, ax\n\t \
		 ret"
	   :
	   : "a" (gdtr));
}