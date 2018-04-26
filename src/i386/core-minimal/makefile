#
# Makefile for OSMOSMC (Open Source Multitasking Operating System [Minimal-Core])
# Made by Alexis BELMONTE
#

# Global settings for Make and it's interpreter:
MAKEFLAGS		   += --silent
SHELL			   := /bin/bash

# Project compiler settings:
ASM					= nasm
ASMFLAGS			= -f elf32
LD					= x86_64-linux-gnu-ld
LDFLAGS				= -g -melf_i386
CXX					= x86_64-linux-gnu-g++
CXXFLAGS			= -g -ffreestanding -O2 -Wall -Wextra -fno-exceptions -nostdlib -fno-builtin -fno-rtti -masm=intel -m32

# Auto-generated variables, DON'T TOUCH !
SOURCE_FILES		= $(shell find . -name '*.cpp')
OUTPUT_FILES		= $(subst ./,$(FOLDER_BINARY)/core-minimal//,$(subst .cpp,.elf,$(SOURCE_FILES)))
SOURCE_FOLDERS		= $(shell find . -mindepth 1 -type d)
OUTPUT_FOLDERS		= $(subst ./,$(FOLDER_BINARY)/core-minimal//,$(SOURCE_FOLDERS))

# The default recipe ran if the makefile is called from command-line
default:
	echo -e "You can't launch this makefile manually because some global variables\ndefined by the root makefile are necessary (such as the source and binary folder).\nPlease run $(MAKE) in the main folder of the OSMOS project.";

# Default recipe for cleaning, building the core kernel, checking if the binary generated is multiboot2 compliant, and copying onto the virtual disk
build: build.clean build.base build.check build.cpkernel

build.clean:
	echo -en "Cleaning kernel base folder... ";
	if [ -d $(FOLDER_BINARY)/core-minimal/ ]; then rm -rf $(FOLDER_BINARY)/core-minimal/; fi;
	mkdir $(FOLDER_BINARY)/core-minimal/;
	echo -e "mkdir done";

build.base:
	echo -en "Generating binary folders... ";
	for OUTPUT_FOLDER in $(OUTPUT_FOLDERS); do \
		mkdir $$OUTPUT_FOLDER; \
	done;
	echo -e "mkdir done";

	echo -en "Building kernel base...\n";
	$(ASM) base.asm -o $(FOLDER_BINARY)/core-minimal/base.elf $(ASMFLAGS);
	echo -e "$(FOLDER_SOURCE)/core-minimal/base.asm (assembled)";

	for SOURCE_FILE in $(SOURCE_FILES); do \
		SPASS=$${SOURCE_FILE/.cpp/.elf}; \
		SRESU="$$(echo $(CXX) -o "$${SPASS/.\//$(FOLDER_BINARY)/core-minimal/\/}" -c $$SOURCE_FILE $(CXXFLAGS))"; \
		FPASS="$$(echo $${SOURCE_FILE/.\//})"; \
		FNAME="$$(echo $${FPASS/.cpp/})"; \
		$$SRESU; \
		echo -e "$(FOLDER_SOURCE)/core-minimal/$$SOURCE_FILE (compiled)"; \
	done;

	$(LD) -o $(FOLDER_BINARY)/core-minimal/boot.bin -T linker.ld $(FOLDER_BINARY)/core-minimal/base.elf $(OUTPUT_FILES) $(LDFLAGS);
	echo -e "$(FOLDER_SOURCE)/core-minimal/linker.ld (linked)";

build.check:
	echo -en "Checking if binary is multiboot compliant... ";
	grub-file --is-x86-multiboot2 $(FOLDER_BINARY)/core-minimal//boot.bin; \
	if [ "$$?" == "0" ]; then \
		echo -e "compliant-ok done"; \
	else \
		echo -e "compilant-fail. Please check if linking is correct."; \
		exit 1; \
	fi;

build.cpkernel:
	echo -en "Copying kernel core... ";
	if [ -d $(FOLDER_VDRIVE) ]; then \
		if [ -d $(FOLDER_VDRIVE)/boot/core/ ]; then sudo rm -rf $(FOLDER_VDRIVE)/boot/core/; fi; \
		sudo mkdir $(FOLDER_VDRIVE)/boot/core/; \
		echo -en "mkdir "; \
		sudo cp -f $(FOLDER_BINARY)/core-minimal//boot.bin $(FOLDER_VDRIVE)/boot/core/boot.bin; \
		echo -e "cpcore done"; \
	else \
		echo -e "fail: vdrive not mounted"; \
	fi;