#
# Makefile for OSMOS (Open Source Multitasking Operating System)
# Made by Alexis BELMONTE
#

# Global settings for Make and it's interpreter:
MAKEFLAGS		   += --silent
SHELL			   := /bin/bash

# Project binary requisites:
PROJECT_REQUISITES	= realpath nasm ld gcc g++ qemu-system-i386

# Project settings for OSMOS:
FOLDER_SOURCE		= src
FOLDER_BINARY		= bin
FOLDER_VDRIVE		= /media/$$USER/osmos-hdd
FOLDER_VLOOP		= /dev/loop0

# Default recipe (when using "make" without arguments)
all: workspace.check build.all run

workspace.check:
	# Check for missing programs
	for REQUISITE in $(PROJECT_REQUISITES); do \
		echo -ne "Checking $$REQUISITE... "; \
		if hash $$REQUISITE 1>/dev/null; then \
			echo -e "found"; \
		else \
			echo -e "not found\nYou can find and install the specific package by using the distribution's package manager (usually apt(itude), pacman, or yum, with administrator privileges)"; \
			exit 1; \
		fi; \
	done;

	# We want to only know if grub-install & grub-file exists
	echo -ne "Checking grub-tools... ";
	if [[ -e /usr/sbin/grub-install && -e /usr/bin/grub-file ]]; then \
		echo -e "found"; \
	else \
		echo -e "not found\nYou can find and install the specific package by using the distribution's package manager (usually apt(itude), pacman, or yum, with administrator privileges)"; \
		exit 1; \
	fi; \

workspace.generate:
	# Check if the setup was already done
	if [ -f $(FOLDER_SOURCE)/.setup_lock ]; then \
		echo -en "WARNING: Build workspace is already setuped. Are you sure to setup the workspace again ? (y/N) "; \
		read -rn1 setup_choice; \
		echo -e ""; \
		if [[ "$$setup_choice" == "y" || "$$setup_choice" == "Y" ]]; then \
			echo -e "Acknowledged. Workspace will be re-built"; \
			rm $(FOLDER_SOURCE)/.setup_lock; \
		else \
			echo -e "Cancelled. Workspace will NOT be re-built"; \
			exit 1; \
		fi; \
	fi;

	# Generate the folders
	echo -en "Generating folders... ";
	if [ ! -d $(FOLDER_SOURCE) ]; then mkdir $(FOLDER_SOURCE); fi
	if [ -d $(FOLDER_BINARY) ]; then rm -rf $(FOLDER_BINARY); fi
	mkdir $(FOLDER_BINARY);
	echo -e "done";

	# Create the file in order to check later if the setup was already done
	touch $(FOLDER_SOURCE)/.setup_lock;

	echo -e "Workspace ready.";

# Recipe for checking + generating the workspace
workspace.setup: workspace.check workspace.generate

# Recipe for cleaning, building both the image and the system, then unmounting (?)
build.all-force: build.check-workspace build.clean build.image build.system build.image.unmount
build.all: build.check-workspace build.image.mount build.system build.image.unmount

build.check-workspace:
	# Check if the workspace has been setuped
	echo -en "Checking workspace setup... ";
	if [ -f $(FOLDER_SOURCE)/.setup_lock ]; then \
		echo -e "done"; \
	else \
		echo -e "missing"; \
		echo -e "Please run \"make workspace.setup\" in order to setup the workspace environment."; \
		exit 1; \
	fi;

build.clean:
	# Clean the folders
	echo -en "Cleaning folders... ";
	if [ -d $(FOLDER_BINARY) ]; then rm -rf $(FOLDER_BINARY); fi
	echo -e "done";

	# Generate the folders
	echo -en "Generating folders... ";
	if [ ! -d $(FOLDER_BINARY) ]; then mkdir $(FOLDER_BINARY); fi
	echo -e "done";

build.system:
	# Build the system by searching all "makefile"s in source directory
	echo -e "Building OSMOS system... ";
	for SUB_MAKEFILE in `find $(FOLDER_SOURCE)/ -type f -name "makefile" -exec echo -en {} \;`; do \
		echo -e "Building $$SUB_MAKEFILE:"; \
		$(MAKE) -C `dirname $$SUB_MAKEFILE`; \
	done;

build.image: build.image.generate build.image.mount-image build.image.mkfs build.image.mount-fs build.image.grub build.image.unmount

build.image.generate:
	# Generate an image by filling a file of \0 by 512*65536 times/65536 sectors
	echo -en "Generating image... ";
	dd if=/dev/zero of=$(FOLDER_BINARY)/hdd.img bs=512 count=65536 status=noxfer 2>>/dev/null
	echo -en "dd ";
	# Automaticly create a new EXT4 partition inside of fdisk
	echo -en "n\np\n1\n\n\na\nw\n" | sudo fdisk $(FOLDER_BINARY)/hdd.img>>/dev/null
	echo -e "fdisk done";

build.image.mkfs:
	# Create a new EXT4 filesystem in the first partition of the loop device
	echo -n "Generating ext4 filesystem... ";
	sudo mkfs.ext4 -q $(FOLDER_VLOOP)p1;
	echo -e "mkfs done";

build.image.mount: build.image.mount-image build.image.mount-fs

build.image.mount-image:
	if [ ! -f $(FOLDER_BINARY)/hdd.img ]; then make build.image; fi;

	# Mount the image in a loopback device
	echo -en "Mounting image... ";
	# Probing is needed in order to use partitions inside imag 
	if grep -qs "$(FOLDER_VLOOP)" /proc/mounts; then \
		echo -e "already mounted"; \
	else \
		sudo losetup $(FOLDER_VLOOP) ./$(FOLDER_BINARY)/hdd.img>>/dev/null; \
		sudo partprobe $(FOLDER_VLOOP); \
		echo -e "mount done"; \
	fi;

build.image.mount-fs:
	# Mount the filesystem by telling that we want the first partition to be mounted
	echo -en "Mounting filesystem... ";
	if [ ! -d $(FOLDER_VDRIVE) ]; then sudo mkdir $(FOLDER_VDRIVE); fi;
	if grep -qs "$(FOLDER_VLOOP)p1" /proc/mounts; then \
		echo -e "already mounted"; \
	else \
		sudo mount $(FOLDER_VLOOP)p1 $(FOLDER_VDRIVE); \
		echo -e "mount done"; \
	fi;

build.image.unmount: build.image.unmount-image build.image.unmount-fs

build.image.unmount-image:
	# Unmount the image properly
	echo -en "Unmounting image... "
	sudo losetup -d $(FOLDER_VLOOP)
	echo -e "unmount done"

build.image.unmount-fs:
	# Unmount the filesystem by telling that we want the first partition to be unmounted
	echo -en "Unmounting filesystem... ";
	sudo umount $(FOLDER_VDRIVE);
	if [ -d $(FOLDER_VDRIVE) ]; then sudo rmdir $(FOLDER_VDRIVE); fi;
	echo -e "unmount done";

build.image.grub:
	# Lots of explaination here - We first add the base folders for GRUB
	echo -en "Installing GRUB onto virtual image... ";
	sudo mkdir $(FOLDER_VDRIVE)/boot;
	sudo mkdir $(FOLDER_VDRIVE)/boot/grub;
	sudo mkdir $(FOLDER_VDRIVE)/boot/core;
	echo -en "mkdir ";
	# Then, we specify the hard-disk device map (when in the virtual machine, it will be identified as the first HDD [sda => hd0])
	echo -en "(hd0) /dev/sda" | sudo tee --append $(FOLDER_VDRIVE)/boot/grub/device.map >> /dev/null
	# We install GRUB
	sudo grub-install --no-floppy --grub-mkdevicemap=$(FOLDER_VDRIVE)/boot/grub/device.map --root-directory=$(FOLDER_VDRIVE)/ ./$(FOLDER_BINARY)/hdd.img 0>>/dev/null 1>>/dev/null 2>>/dev/null
	# We add the necessary entry in order to boot into OSMOS (with the multiboot2 specification)
	echo -en "mkgrub ";
	echo -en "menuentry 'OSMOS kernel' {\necho 'Starting OSMOS...'\nset root='hd0,1'\nmultiboot2 /boot/core/boot.bin\n}" | sudo tee --append $(FOLDER_VDRIVE)/boot/grub/grub.cfg >> /dev/null
	# and finished !
	echo -e "mkconfig done";

run:
	# Runs GDT and the QEMU emulator
	cd src;
	qemu-system-i386 -S -m 128M -k fr -hda ./$(FOLDER_BINARY)/hdd.img -gdb tcp::23583 & \
	gdb -ex "target remote localhost:23583" \
		-ex "symbol-file $(FOLDER_BINARY)/core-minimal/boot.bin" \
	cd ..;
