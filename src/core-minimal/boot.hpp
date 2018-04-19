/*
 * The Boot header, main point of the core-minimal kernel
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
#ifndef BOOT_H
#define BOOT_H

#include "common/string.hpp"
#include "common/common.hpp"
#include "common/system/mem.hpp"
#include "common/system/gdt/gdt.hpp"
#include "io/vga_display.hpp"
#include "io/pci/pci.hpp"
#include "multiboot2/multiboot2.hpp"

/***
 * :name Boot
 * :brief The main class of the core-minimal kernel (1st stage)
 * :description {
 *  	The main class of the core-minimal kernel, which is the most essential
 *  	part of starting up OSMOS. It loads his own global descriptor table
 *      and detects the devices present on the computer such as PCI (in order to
 *  	do input/output operations to IDE disk drives), ATA (in order to do
 *      input/output operations to ATA disk drives). He then fills the Boot
 *  	structure table, to give it to the second stage of the operating system,
 *      loaded by reading the EXTended file system (FAT and NTFS will NOT be
 *  	compatible with OSMOS' core-minimal kernel, because of it's messy way
 *  	to manage himself).
 * }
 ***/
class Boot {
public:
	/***
	 * :name Boot::Structure
	 * :brief The boot structure, containing the bare essentials for starting \
	 * up the core-main kernel (2nd stage)
	 * :description {
	 *  	The boot structure, or the parameter boot structure (PBS) is a
	 *  	structure that is very important for the core-main kernel. It
	 *  	contains the bootloader arguments, the bootloader name (such as
	 *  	GRUB <version>), the module list, the memory map, and a copy of
	 *  	the global descriptor table and it's pointer.
	 * }
	 ***/
	struct Structure {
		char *bootloader_args;
		char *bootloader_name;
		Multiboot::Tag::Module *modules;
		Multiboot::Tag::BootDevice *boot_device;
		Multiboot::Tag::MemoryMap *memory_map;
		System::GDT::Entry gdTable;
		System::GDT::Pointer gdPointer;
	};

	/***
	 * <group "var+gdt&struct">
	 * :name Boot::gdTable
	 * :brief The global descriptor table for the core-minimal kernel
	 ***/
	static System::GDT::Entry gdTable[5];
	/***
	 * :name Boot::gdPointer
	 * :brief The global descriptor table pointer
	 ***/
	static System::GDT::Pointer gdPointer;
	/***
	 * :name Boot::structure
	 * :brief The <see Boot::Structure>boot structure</see> for the core-main \
	 * kernel (2nd stage)
	 ***/
	static Boot::Structure structure;

	/***
	 * :name Boot::forEachDevice(...)
	 * :brief The forEachDevice for the PCI device detection
	 ***/
	static void forEachDevice(IO::PCI::CAM::BasicDevice *device, int index);
	/***
	 * </group "var+gdt&struct">
	 ***/
	
	/***
	 * <group "var+ideDevices">
	 * :name Boot::ideDevices
	 * :brief The list of IDE devices found of the computer
	 ***/
	static IO::PCI::CAM::BasicDevice *ideDevices[4];
	/***
	 * :name Boot::ideDeviceIndex
	 * :brief The index of the IDE device, only used for ideDevices.
	 ***/
	static int ideDeviceIndex;
	/***
	 * </group>
	 ***/
};

/***
 * :attribute +language=c
 * :name kboot(...)
 * :brief The core kernel main function, called after being loaded by GRUB
 ***/
extern "C" void kboot(uint_32 magic, uint_32 table_address);

#endif