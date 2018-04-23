/*
 * The Multiboot header, adapted from the C multiboot2 header given by
 * GRUB's manual. See https://www.gnu.org/software/grub/manual/multiboot2/
 * for more details.
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

#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "../common/common.hpp"

#define MULTIBOOT_HEADER_MAGIC					 0xE85250D6
#define MULTIBOOT_BOOT_MAGIC					 0x36D76289
#define MULTIBOOT_MOD_ALIGN						 0x00001000
#define MULTIBOOT_INFO_ALIGN					 0x00000008

#define MULTIBOOT_TAG_ALIGN				    	 8
#define MULTIBOOT_TAG_TYPE_END				 	 0
#define MULTIBOOT_TAG_TYPE_CMDLINE		    	 1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME  	 2
#define MULTIBOOT_TAG_TYPE_MODULE		     	 3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     	 4
#define MULTIBOOT_TAG_TYPE_BOOTDEV		    	 5
#define MULTIBOOT_TAG_TYPE_MMAP					 6
#define MULTIBOOT_TAG_TYPE_VBE				 	 7
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER			 8
#define MULTIBOOT_TAG_TYPE_ELF_SECTIONS      	 9
#define MULTIBOOT_TAG_TYPE_APM				 	 10
#define MULTIBOOT_TAG_TYPE_EFI32		      	 11
#define MULTIBOOT_TAG_TYPE_EFI64		      	 12
#define MULTIBOOT_TAG_TYPE_SMBIOS		     	 13
#define MULTIBOOT_TAG_TYPE_ACPI_OLD				 14
#define MULTIBOOT_TAG_TYPE_ACPI_NEW				 15
#define MULTIBOOT_TAG_TYPE_NETWORK				 16
#define MULTIBOOT_TAG_TYPE_EFI_MMAP				 17
#define MULTIBOOT_TAG_TYPE_EFI_BS				 18
#define MULTIBOOT_TAG_TYPE_EFI32_IH				 19
#define MULTIBOOT_TAG_TYPE_EFI64_IH				 20
#define MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR		 21
     
#define MULTIBOOT_HEADER_TAG_END				 0
#define MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST 1
#define MULTIBOOT_HEADER_TAG_ADDRESS			 2
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS		 3
#define MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS		 4
#define MULTIBOOT_HEADER_TAG_FRAMEBUFFER		 5
#define MULTIBOOT_HEADER_TAG_MODULE_ALIGN		 6
#define MULTIBOOT_HEADER_TAG_EFI_BS				 7
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI32 8
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI64 9
#define MULTIBOOT_HEADER_TAG_RELOCATABLE		 10

#define MULTIBOOT_ARCHITECTURE_I386				 0
#define MULTIBOOT_ARCHITECTURE_MIPS32			 4
#define MULTIBOOT_HEADER_TAG_OPTIONAL			 1

#define MULTIBOOT_LOAD_PREFERENCE_NONE			 0
#define MULTIBOOT_LOAD_PREFERENCE_LOW			 1
#define MULTIBOOT_LOAD_PREFERENCE_HIGH			 2

#define MULTIBOOT_CONSOLE_FLAGS_CONSOLE_REQUIRED 1
#define MULTIBOOT_CONSOLE_FLAGS_EGA_SUPPORTED	 2

#define MULTIBOOT_MEMORY_AVAILABLE               1
#define MULTIBOOT_MEMORY_RESERVED                2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE        3
#define MULTIBOOT_MEMORY_NVS                     4
#define MULTIBOOT_MEMORY_BADRAM                  5

#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED		 0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB			 1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT		 2

/*
 * Most of the structures are directly based from the following header:
 * https://www.gnu.org/software/grub/manual/multiboot2/html_node/multiboot2_002eh.html#multiboot2_002eh
 * Please see license details of this header for more details.
 */
namespace Multiboot {
	class Header {
	public:
		struct Tag
		{
			uint_16 type;
			uint_16 flags;
			uint_32 size;
		};

		struct Tag_InformationRequest
		{
			uint_16 type;
			uint_16 flags;
			uint_32 size;
			uint_32 requests[0];
		};

		struct Tag_Address
		{
			uint_16 type;
			uint_16 flags;
			uint_32 size;
			uint_32 header_addr;
			uint_32 load_addr;
			uint_32 load_end_addr;
			uint_32 bss_end_addr;
		};

		struct Tag_EntryAddress
		{
			uint_16 type;
			uint_16 flags;
			uint_32 size;
			uint_32 entry_addr;
		};

		struct Tag_ConsoleFlags
		{
			uint_16 type;
			uint_16 flags;
			uint_32 size;
			uint_32 console_flags;
		};

		struct Tag_Framebuffer
		{
			uint_16 type;
			uint_16 flags;
			uint_32 size;
			uint_32 width;
			uint_32 height;
			uint_32 depth;
		};

		struct Tag_ModuleAlign
		{
			uint_16 type;
			uint_16 flags;
			uint_32 size;
		};

		struct Tag_Relocatable
		{
			uint_16 type;
			uint_16 flags;
			uint_32 size;
			uint_32 min_addr;
			uint_32 max_addr;
			uint_32 align;
			uint_32 preference;
		};
	};

	class Common {
	public:
		struct Color
		{
			uint_8 red;
			uint_8 green;
			uint_8 blue;
		};

		struct MemoryMapEntry
		{
			uint_64 addr;
			uint_64 len;
			uint_32 type;
			uint_32 zero;
		};
	};

	class Tag {
	public:
		struct BasicTag
		{
			uint_32 type;
			uint_32 size;
		};

		struct String
		{
			uint_32 type;
			uint_32 size;
			char string[0];
		};

		struct Module
		{
			uint_32 type;
			uint_32 size;
			uint_32 mod_start;
			uint_32 mod_end;
			char cmdline[0];
		};

		struct Basic_MemoryInformation
		{
			uint_32 type;
			uint_32 size;
			uint_32 mem_lower;
			uint_32 mem_upper;
		};

		struct BootDevice
		{
			uint_32 type;
			uint_32 size;
			uint_32 biosdev;
			uint_32 slice;
			uint_32 part;
		};

		struct MemoryMap
		{
			uint_32 type;
			uint_32 size;
			uint_32 entry_size;
			uint_32 entry_version;
			struct Common::MemoryMapEntry entries[0];
		};

		struct VBE_InformationBlock
		{
			uint_8 external_specification[512];
		};

		struct VBE_Mode_InformationBlock
		{
			uint_8 external_specification[256];
		};

		struct VBE
		{
			uint_32 type;
			uint_32 size;

			uint_16 vbe_mode;
			uint_16 vbe_interface_seg;
			uint_16 vbe_interface_off;
			uint_16 vbe_interface_len;
     
			struct VBE_InformationBlock vbe_control_info;
			struct VBE_Mode_InformationBlock vbe_mode_info;
		};

		struct Framebuffer_Common {
			uint_32 type;
			uint_32 size;

			uint_64 framebuffer_addr;
			uint_32 framebuffer_pitch;
			uint_32 framebuffer_width;
			uint_32 framebuffer_height;
			uint_8 framebuffer_bpp;

			uint_8 framebufferype;
			uint_16 reserved;
		};

		struct Framebuffer
		{
			struct Framebuffer_Common common;
     
			union
			{
				struct
				{
					uint_16 framebuffer_palette_num_colors;
					struct Common::Color framebuffer_palette[0];
				};
         		struct
				{
					uint_8 framebuffer_red_field_position;
					uint_8 framebuffer_red_mask_size;
					uint_8 framebuffer_green_field_position;
					uint_8 framebuffer_green_mask_size;
					uint_8 framebuffer_blue_field_position;
					uint_8 framebuffer_blue_mask_size;
				};
			};
		};

		struct ELF_Sections
		{
			uint_32 type;
			uint_32 size;
			uint_32 num;
			uint_32 entsize;
			uint_32 shndx;
			char sections[0];
		};

		struct APM
		{
			uint_32 type;
			uint_32 size;
			uint_16 version;
			uint_16 cseg;
			uint_32 offset;
			uint_16 cseg_16;
			uint_16 dseg;
			uint_16 flags;
			uint_16 cseg_len;
			uint_16 cseg_16_len;
			uint_16 dseg_len;
		};

		struct EFI32
		{
			uint_32 type;
			uint_32 size;
			uint_32 pointer;
		};

		struct EFI64
		{
			uint_32 type;
			uint_32 size;
			uint_64 pointer;
		};

		struct SMBIOS
		{
			uint_32 type;
			uint_32 size;
			uint_8 major;
			uint_8 minor;
			uint_8 reserved[6];
			uint_8 tables[0];
		};

		struct ACPI_Old
		{
			uint_32 type;
			uint_32 size;
			uint_8 rsdp[0];
		};

		struct ACPI_New
		{
			uint_32 type;
			uint_32 size;
			uint_8 rsdp[0];
		};

		struct Network
		{
			uint_32 type;
			uint_32 size;
			uint_8 dhcpack[0];
		};

		struct EFI_MemoryMap
		{
			uint_32 type;
			uint_32 size;
			uint_32 descr_size;
			uint_32 descr_vers;
			uint_8 efi_mmap[0];
		};

		struct EFI32_IH
		{
			uint_32 type;
			uint_32 size;
			uint_32 pointer;
		};

		struct EFI64_IH
		{
			uint_32 type;
			uint_32 size;
			uint_64 pointer;
		};

		struct Load_BaseAddress
		{
			uint_32 type;
			uint_32 size;
			uint_32 load_base_addr;
		};
	};
};

#endif