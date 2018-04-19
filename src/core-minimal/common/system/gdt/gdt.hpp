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

#ifndef GDT_H
#define GDT_H

#include "../../common.hpp"

namespace System {
	class GDT {
	public:
		struct Entry {
			uint_16 limit_low;
			uint_16 base_low;
			uint_8 base_middle;
			uint_8 access;
			uint_8 limit_high_flags;
			uint_8 base_high;
		} __attribute__((packed));

		struct Pointer {
			uint_16 size;
			uint_32 base;
		} __attribute__((packed));

		static const uint_8 ENTRY_FLAG_NONE;
		static const uint_8 ENTRY_FLAG_BIG_SIZE;
		static const uint_8 ENTRY_FLAG_GRANULARITY;

		static const uint_8 ACCESS_FLAG_NONE;
		static const uint_8 ACCESS_FLAG_ACCESSED;
		static const uint_8 ACCESS_FLAG_READ_WRITE;
		static const uint_8 ACCESS_FLAG_DIRECTION_CONFORMING;
		static const uint_8 ACCESS_FLAG_EXECUTABLE;
		static const uint_8 ACCESS_FLAG_REQUIRED;
		static const uint_8 ACCESS_FLAG_PRESENT;

		static const uint_8 ACCESS_PRIVILEGE_KERNEL_MODE;
		static const uint_8 ACCESS_PRIVILEGE_ADMINISTRATIVE_MODE;
		static const uint_8 ACCESS_PRIVILEGE_MODERATIVE_MODE;
		static const uint_8 ACCESS_PRIVILEGE_USER_MODE;

		static void initializeEntry(uint_32 base, uint_32 limit, uint_8 access, uint_8 flags, struct System::GDT::Entry *gdt);
		static void setTable(struct System::GDT::Pointer *gdtr, struct System::GDT::Entry *gdt, uint_32 size);
	};
};

#endif