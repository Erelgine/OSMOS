/**
 * @file core-minimal/boot.cpp
 * @brief The initial main point of the core-minimal kernel
 **/

/*
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

#include "osmos/osmos.hpp"

#include "osmos/io/serial.hpp"
#include "osmos/sys/memory.hpp"

extern "C"
void kboot(uint32_t magic, uint32_t table_address) {
    size_t baseAddress = 0;
    asm("mov %[base], _eof"
       :
       : [base] "a" (baseAddress));

    OSMOS::System::Memory::setBaseAddress(baseAddress);
    OSMOS::System::Memory::setLimitAddress(baseAddress + 512 * 1024);

    uint16_t *screen = (uint16_t *) 0xB8000;
    screen[0] = 0xF040;

    OSMOS::IO::SerialPort *debug = new OSMOS::IO::SerialPort(OSMOS::IO::SerialPort::COMMUNICATION_PORT_1);
    debug->out("Hello, this is a test message !");
    screen[1] = 0xF040;

    screen[2] = 0xF040;
}
