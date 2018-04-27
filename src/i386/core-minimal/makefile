#
# Makefile for OSMOS-CM (Open Source Multitasking Operating System [core-minimal])
# Made by Alexis BELMONTE
#

# Global settings for Make and it's interpreter:
MAKEFLAGS                   += --silent
SHELL                       := /bin/bash

# Auto-generated variables, DON'T TOUCH !
CPP_SOURCE_FILES             = $(shell find . -name '*.cpp' -printf "$(FOLDER_SOURCE)/core-minimal/%p ")
ASM_SOURCE_FILES             = $(shell find . -name '*.asm' -printf "$(FOLDER_SOURCE)/core-minimal/%p ")

CPP_OUTPUT_FILES             = $(subst .cpp,.elf,$(subst $(FOLDER_SOURCE),$(FOLDER_BINARY),$(CPP_SOURCE_FILES)))
ASM_OUTPUT_FILES             = $(subst .asm,.elf,$(subst $(FOLDER_SOURCE),$(FOLDER_BINARY),$(ASM_SOURCE_FILES)))

SOURCE_FOLDERS               = $(shell find . -mindepth 1 -type d)
OUTPUT_FOLDERS               = $(subst ./,$(FOLDER_BINARY)/core-minimal/,$(SOURCE_FOLDERS))

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

	echo -e "Building kernel base...";
	for SOURCE_FILE in $(ASM_SOURCE_FILES); do \
		SOURCE_FILE="$$(echo $${SOURCE_FILE/.\//})"; \
		__OUTPUT_FILE="$$(echo $${SOURCE_FILE/.asm/.elf})"; \
		OUTPUT_FILE="$$(echo $${__OUTPUT_FILE/$$FOLDER_SOURCE/$$FOLDER_BINARY})"; \
		$(ASM) -o $$OUTPUT_FILE $$SOURCE_FILE $(ASMFLAGS); \
		if [ "$$?" != "0" ]; then \
			echo -e "$$SOURCE_FILE failed"; \
			exit 1; \
		fi; \
		echo -e "$$SOURCE_FILE (assembled)"; \
	done;

	for SOURCE_FILE in $(CPP_SOURCE_FILES); do \
		SOURCE_FILE="$$(echo $${SOURCE_FILE/.\//})"; \
		__OUTPUT_FILE="$$(echo $${SOURCE_FILE/.cpp/.elf})"; \
		OUTPUT_FILE="$$(echo $${__OUTPUT_FILE/$$FOLDER_SOURCE/$$FOLDER_BINARY})"; \
		$(CXX) -o $$OUTPUT_FILE -c $$SOURCE_FILE $(CXXFLAGS); \
		if [ "$$?" != "0" ]; then \
			echo -e "$$SOURCE_FILE failed"; \
			exit 1; \
		fi; \
		echo -e "$$SOURCE_FILE (compiled)"; \
	done;

	$(LD) -o $(FOLDER_BINARY)/core-minimal/boot.bin -T linker.ld $(ASM_OUTPUT_FILES) $(CPP_OUTPUT_FILES) $(LDFLAGS);
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