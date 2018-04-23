/*
 * The Boot class, main point of the core-minimal kernel
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

/*
 * The main boot class. See <see +file="boot.hpp">boot.hpp</see> for
 * function details.
 */

/***
 * :name "Include directive"
 * :brief The include directive for the <see +file boot.cpp>boot.hpp</see> \
 * header file
 ***/
#include "boot.hpp"

/***
 * :attribute +applygroup
 * :brief Include directives for many objects and classes
 ***/
#include "common/string.hpp"
#include "common/common.hpp"
#include "common/system/mem.hpp"
#include "common/system/gdt/gdt.hpp"
#include "io/vga_display.hpp"
#include "io/pci/pci.hpp"
#include "multiboot2/multiboot2.hpp"

/***
 * :attribute +link("var+gdt&struct") +applygroup
 ***/
System::GDT::Entry Boot::gdTable[5];
System::GDT::Pointer Boot::gdPointer;
Boot::Structure Boot::structure;

/***
 * :attribute +link("var+ideDevices") +applygroup
 ***/
IO::PCI::CAM::BasicDevice *Boot::ideDevices[4];
int Boot::ideDeviceIndex;

/***
 * :attribute +link
 ***/
void Boot::forEachDevice(IO::PCI::CAM::BasicDevice *device, int index) {
	/*
	 * The following check if the PCI device is a <see file="io/pci/pci.hpp" \
	 * IO::PCI::Class::Storage>storage device</see>, and is of type IDE. If it
	 * is the case, it just adds to the <see Boot::ideDevices>Boot::ideDevices
	 * </see> table and increments it's <see Boot::ideDeviceIndex>index</see>.
	 */
	if (device->class_code == IO::PCI::Class::Storage::CLASS_CODE && device->class_code == 0x1) {
		Boot::ideDevices[Boot::ideDeviceIndex] = (IO::PCI::CAM::BasicDevice *) System::Memory::allocateBlock(sizeof(IO::PCI::CAM::BasicDevice));
		System::Memory::copy((char *) Boot::ideDevices[Boot::ideDeviceIndex], (char *) device, sizeof(IO::PCI::CAM::BasicDevice));
		Boot::ideDeviceIndex++;
	}
}

/***
 * :attribute +link
 ***/
extern "C"
void kboot(uint_32 magic, uint_32 table_address) {
	/*
	 * The first three lines enables the cursor, sets the cursor position to
	 * coordinates 0, 0 and clears the screen
	 */
	IO::VGADisplay::enableCursor();
	IO::VGADisplay::setCursorPosition(0, 0);
	IO::VGADisplay::clear();

	/*
	 * Then, we load the global descriptor table by first displaying the
	 * loading message, then filling the entries and finally giving it
	 * to the processor.
	 */
	IO::VGADisplay::putString("Loading descriptor table... ", 0x7, 0x0);
	System::GDT::initializeEntry(0x00000000, 0x00000000,
								System::GDT::ACCESS_FLAG_NONE,
								System::GDT::ENTRY_FLAG_NONE,
								&Boot::gdTable[0]);
	System::GDT::initializeEntry(0x00000000, 0x0007D000,
								System::GDT::ACCESS_FLAG_REQUIRED |
								System::GDT::ACCESS_FLAG_PRESENT |
								System::GDT::ACCESS_FLAG_EXECUTABLE |
								System::GDT::ACCESS_PRIVILEGE_KERNEL_MODE,
								System::GDT::ENTRY_FLAG_GRANULARITY |
								System::GDT::ENTRY_FLAG_BIG_SIZE,
								&Boot::gdTable[1]);
	System::GDT::initializeEntry(0x00000000, 0x0007D000,
								System::GDT::ACCESS_FLAG_REQUIRED |
								System::GDT::ACCESS_FLAG_PRESENT |
								System::GDT::ACCESS_FLAG_READ_WRITE |
								System::GDT::ACCESS_PRIVILEGE_KERNEL_MODE,
								System::GDT::ENTRY_FLAG_GRANULARITY |
								System::GDT::ENTRY_FLAG_BIG_SIZE,
								&Boot::gdTable[2]);
	System::GDT::initializeEntry(0x0007D001, 0xFFFFFFFF,
								System::GDT::ACCESS_FLAG_REQUIRED |
								System::GDT::ACCESS_FLAG_PRESENT |
								System::GDT::ACCESS_FLAG_EXECUTABLE |
								System::GDT::ACCESS_PRIVILEGE_USER_MODE,
								System::GDT::ENTRY_FLAG_GRANULARITY |
								System::GDT::ENTRY_FLAG_BIG_SIZE,
								&Boot::gdTable[3]);
	System::GDT::initializeEntry(0x0007D001, 0xFFFFFFFF,
								System::GDT::ACCESS_FLAG_REQUIRED |
								System::GDT::ACCESS_FLAG_PRESENT |
								System::GDT::ACCESS_FLAG_READ_WRITE |
								System::GDT::ACCESS_PRIVILEGE_USER_MODE,
								System::GDT::ENTRY_FLAG_GRANULARITY |
								System::GDT::ENTRY_FLAG_BIG_SIZE, &Boot::gdTable[4]);
	System::GDT::setTable(&Boot::gdPointer, Boot::gdTable, (uint_32) (64 * 5 - 1));
	IO::VGADisplay::putString("done\n", 0xF, 0x0);

	IO::VGADisplay::putString("Booting from ", 0x7, 0x0);
	
	/*
	 * We need to check if both the magic is correct and the table given
	 * by the multiboot2 compliant bootloader is aligned correctly.
	 */
	if (magic != MULTIBOOT_BOOT_MAGIC) {
		IO::VGADisplay::putString("error: ", 0x7, 0x0);
		IO::VGADisplay::putString("invalid ", 0xF, 0x0);
		IO::VGADisplay::put('[', 0x7, 0x0);
		IO::VGADisplay::putString("0x", 0xF, 0x0);
		IO::VGADisplay::putInteger(magic, 16, 0xF, 0x0);
		IO::VGADisplay::put(']', 0x7, 0x0);
		return;
	}

	if (table_address & (MULTIBOOT_TAG_ALIGN - 1)) {
		IO::VGADisplay::putString("error: ", 0x7, 0x0);
		IO::VGADisplay::putString("unaligned ", 0xF, 0x0);
		IO::VGADisplay::put('[', 0x7, 0x0);
		IO::VGADisplay::putString("0x", 0xF, 0x0);
		IO::VGADisplay::putInteger(table_address, 16, 0xF, 0x0);
		IO::VGADisplay::put(']', 0x7, 0x0);
		return;
	}

	/*
	 * We then gather useful informations from the multiboot2 bootloader.
	 */

	Multiboot::Tag::Module *module_array[256];
	Multiboot::Tag::MemoryMap *mmap_array[16];
	int module_index = 0;
	int mmap_index = 0;

	struct Multiboot::Tag::BasicTag *tag;
	for (tag = (struct Multiboot::Tag::BasicTag *) (table_address + MULTIBOOT_TAG_ALIGN);
		 tag->type != MULTIBOOT_TAG_TYPE_END;
		 tag = (struct Multiboot::Tag::BasicTag *) ((uint_8 *) tag + ((tag->size + (MULTIBOOT_TAG_ALIGN - 1)) & ~(MULTIBOOT_TAG_ALIGN - 1)))) {
		switch (tag->type) {
			/*
			 * We check if the current tag is equal to what we search, and put it in
			 * the <see Boot::Structure>Boot::Structure</see>.
			 */
			case MULTIBOOT_TAG_TYPE_CMDLINE:
				Boot::structure.bootloader_args = ((struct Multiboot::Tag::String *) tag)->string;
				break;
			case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
				Boot::structure.bootloader_name = ((struct Multiboot::Tag::String *) tag)->string;
				break;
			case MULTIBOOT_TAG_TYPE_BOOTDEV:
				Boot::structure.boot_device = ((struct Multiboot::Tag::BootDevice *) tag);
				break;
			case MULTIBOOT_TAG_TYPE_MODULE:
				module_array[module_index] = ((struct Multiboot::Tag::Module *) tag);
				module_index++;
				break;
			case MULTIBOOT_TAG_TYPE_MMAP:
				mmap_array[mmap_index] = ((struct Multiboot::Tag::MemoryMap *) tag);
				mmap_index++;
				break;
		}
	}

	Boot::structure.modules = *module_array;
	Boot::structure.memory_map = *mmap_array;

	/*
	 * We display the multiboot2 compliant bootloader's name and it's
	 * version, and displays any argument given on the multiboot2 command.
	 */
	IO::VGADisplay::putString(Boot::structure.bootloader_name, 0xF, 0x0);
	if (String::length(Boot::structure.bootloader_args) > 0) {
		IO::VGADisplay::putString(" with ", 0x7, 0x0);
		IO::VGADisplay::putString(Boot::structure.bootloader_args, 0xF, 0x0);
	} else
		IO::VGADisplay::putString(" without arguments", 0x7, 0x0);
	IO::VGADisplay::putString("\n", 0x7, 0x0);

	/*
	 * We then scan IDE PCI devices with the <see Boot::forEachDevice> \
	 * Boot::forEachDevice</see> function.
	 */
	IO::VGADisplay::putString("Scanning PCI devices... ", 0x7, 0x0);
	IO::PCI::Device::detect(Boot::forEachDevice);
	IO::VGADisplay::putString("done\n", 0xF, 0x0);

	// TODO: test new and delete functions (may be buggy)
	IO::VGADisplay::putString("Allocating a 4K chunk: ", 0x7, 0x0);
	void *blkptr = System::Memory::allocateBlock(4096);
	if (!blkptr) {
		IO::VGADisplay::putString("fail", 0xC, 0x0);
		while (true);
	}

	IO::VGADisplay::putInteger((uint_32) blkptr, 16, 0xF, 0x0);

	System::Memory::freeBlock(blkptr, 4096);
	IO::VGADisplay::putString("deallocate done\n", 0xF, 0x0);

	while (true);
}
