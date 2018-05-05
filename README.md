# OSMOS
## Description
The Open Source Multitasking Operating System (The OSMOS) that aims to be fast, lightweight, and open-source for everyone. It's goal is to be runnable by any platform from various low and high configurations and flexible to get most out of your computer.

## Project design
### Name
The operating system should be called "The OSMOS", so please use "The OSMOS" in order to differenciate it from the kernel itself which is called "OSMOS".

### Development and project organization
The OSMOS is using simple tools and programming languages such as Intel syntax for both `nasm` and `g++`'s inline assembly. It is organized to group by architecture, but only one is present for the moment; which is the `i386` generation of processors. The OSMOS targets to be an multi-architecture kernel and operating system.

# Building the project
## Downloading and installing the required dependencies
`realpath`, `nasm`, `ld`, `gcc/g++`, `qemu-system-<arch>`, and `gdb` are required in order to build the operating system. You can download and install them by using your distribution's package manager. If you do not know what it is or what does the distribution uses, you shouldn't build OSMOS for now, and instead learn with your distribution's provided documentation or tutorials available on your favorite search engine.

## Downloading the project
In order to download this project, you need to choose a spot for the project folder. Do not worry, you don't need to create a folder for the project as `git` already does make a folder for the project. Launch a terminal, go to the folder you want to store the project (such as the Desktop with the `cd` command) and then type `git clone https://github.com/Erelgine/OSMOS.git --recursive` into the terminal. You should normally download the entire project without losing something.

## Setting up the workspace
In order to setup everything, the `Makefile` needs to create and configure every needed file in order to then build and execute the project. Go to the OSMOS folder (using the `cd` command) and type it in `make setup`. It should normally check if every dependency/requisite is installed properly and constructs a binary folder while generating a virtual hard-disk image called `hdd.img` that will be placed in `bin/<arch>/hdd.img`.

## Manipulating the virtual hard-disk image
### Mounting the virtual hard-disk image
If you want to mount/unmount the pre-generated virtual hard-disk image, type it in the terminal `make build.image.mount` if you want to mount it or `make build.image.unmount` if you want to unmount it. That way, you can access to the contents of it and do operations on present files.

### Regenerating the virtual hard-disk image
If you think that you did something wrong with the generated `hdd.img` file and you want to reset it, you will need to unmount it first, then just use `make build.image.generate` to generate a new one.

### Reinstalling GRUB
If you modified/altered GRUB's configuration and broke the boot entry, you can reinstall GRUB by typing it in `make build.image.grub`. It will re-create GRUB files and re-install everything that is needed in order to start GRUB.

# Contributing
If you want to contribute to the OSMOS' project, you will need to respect the syntax and the way the code is implemented and optimized while adding comments to describe what the code does. You are free to make an alternative way to this kernel, but provide source to the original project and author, otherwise it wouldn't be fair and you could ran into legal issues.
