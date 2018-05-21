cmake_minimum_required(VERSION 3.10)
project(OSMOS)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/i386/core-minimal/osmos)
include_directories(src/i386/core-minimal/osmos/io)
include_directories(src/i386/core-minimal/osmos/sys)

add_executable(OSMOS
        src/i386/core-minimal/osmos/io/port.cpp
        src/i386/core-minimal/osmos/io/port.hpp
        src/i386/core-minimal/osmos/io/serial.cpp
        src/i386/core-minimal/osmos/io/serial.hpp
        src/i386/core-minimal/osmos/sys/cpp/cs.asm
        src/i386/core-minimal/osmos/sys/memory.cpp
        src/i386/core-minimal/osmos/sys/memory.hpp
        src/i386/core-minimal/osmos/osmos.hpp
        src/i386/core-minimal/base.asm
        src/i386/core-minimal/boot.cpp
        src/i386/core-minimal/linker.ld
        src/i386/core-minimal/Makefile
        LICENSE
        Makefile
        README.md)
