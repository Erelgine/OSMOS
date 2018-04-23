#
# Makefile for OSMOSMC (Open Source Multitasking Operating System [Minimal-Core])
# Made by Alexis BELMONTE
#

# Global settings for Make and it's interpreter:
MAKEFLAGS		   += --silent
SHELL			   := /bin/bash

# Project kernel folders:
FOLDER_INCLUDE		= lib
FOLDER_BINARY		= ../../bin/core-minimal
FOLDER_VDRIVE		= /media/$$USER/osmos-hdd

# Project compiler settings:
ASM					= nasm
ASMFLAGS			= -f elf32
LD					= x86_64-linux-gnu-ld
LDFLAGS				= -g -melf_i386
CXX					= x86_64-linux-gnu-g++
CXXFLAGS			= -g -ffreestanding -O2 -Wall -Wextra -fno-exceptions -nostdlib -fno-builtin -fno-rtti -masm=intel -m32

# Auto-generated variables, DON'T TOUCH !
SOURCE_FILES		= $(shell find . -name '*.cpp')
OUTPUT_FILES		= $(subst ./,$(FOLDER_BINARY)/,$(subst .cpp,.elf,$(SOURCE_FILES)))
SOURCE_FOLDERS		= $(shell find . -mindepth 1 -type d)
OUTPUT_FOLDERS		= $(subst ./,$(FOLDER_BINARY)/,$(SOURCE_FOLDERS))

# Default recipe for cleaning, building the core kernel, checking if the binary generated is multiboot2 compliant, and copying onto the virtual disk
build: build.clean build.base build.check build.cpkernel

build.clean:
	echo -en "Cleaning kernel base folder... ";
	if [ -d $(FOLDER_BINARY) ]; then rm -rf $(FOLDER_BINARY); fi;
	mkdir $(FOLDER_BINARY);
	echo -e "mkdir done";

build.base:
	echo -en "Generating binary folders... ";
	for OUTPUT_FOLDER in $(OUTPUT_FOLDERS); do \
		mkdir $$OUTPUT_FOLDER; \
	done;
	echo -e "mkdir done";

	echo -en "Building kernel base... ";
	$(ASM) base.asm -o $(FOLDER_BINARY)/base.elf $(ASMFLAGS);
	echo -en "base-asm ";

	for SOURCE_FILE in $(SOURCE_FILES); do \
		SPASS=$${SOURCE_FILE/.cpp/.elf}; \
		SRESU="$$(echo $(CXX) -o "$${SPASS/.\//$(FOLDER_BINARY)\/}" -c $$SOURCE_FILE $(CXXFLAGS))"; \
		FPASS="$$(echo $${SOURCE_FILE/.\//})"; \
		FNAME="$$(echo $${FPASS/.cpp/})"; \
		$$SRESU; \
		echo -en $$FNAME" "; \
	done;

	$(LD) -o $(FOLDER_BINARY)/boot.bin -T linker.ld $(FOLDER_BINARY)/base.elf $(OUTPUT_FILES) $(LDFLAGS);
	echo -e "base-ld done";

build.check:
	echo -en "Checking if binary is multiboot compliant... ";
	grub-file --is-x86-multiboot2 $(FOLDER_BINARY)/boot.bin; \
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
		sudo cp -f $(FOLDER_BINARY)/boot.bin $(FOLDER_VDRIVE)/boot/core/boot.bin; \
		echo -e "cpcore done"; \
	else \
		echo -e "fail: vdrive not mounted"; \
	fi;