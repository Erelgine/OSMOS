/*
 * The boot file
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

#include "osmos/io/port.hpp"
#include "osmos/sys/memory.hpp"

extern "C"
void kboot(uint32_t magic, uint32_t table_address) {
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 1, (uint8_t) 0x00);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 3, (uint8_t) 0x80);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 0, (uint8_t) 0x03);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 1, (uint8_t) 0x00);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 3, (uint8_t) 0x03);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 2, (uint8_t) 0xC7);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 4, (uint8_t) 0x0B);

    OSMOS::IO::Port::out((uint16_t) 0x3F8, "Initializating memory allocation... ");
    
    address_t baseAddress = 0;
    asm("mov %[base], _eof"
       :
       : [base] "a" (baseAddress));

    OSMOS::System::Memory::setBaseAddress(baseAddress);
    OSMOS::System::Memory::setLimitAddress(baseAddress + 128 * 1024);
    OSMOS::IO::Port::out((uint16_t) 0x3F8, "done\r\n");

    OSMOS::IO::Port::out((uint16_t) 0x3F8, "Allocating 16 bytes block... ");
    char *str = (char *) OSMOS::System::Memory::allocateBlock(16);
    OSMOS::IO::Port::out((uint16_t) 0x3F8, "...and another 16 bytes block... ");
    char *dat = (char *) OSMOS::System::Memory::allocateBlock(16);
    OSMOS::IO::Port::out((uint16_t) 0x3F8, "done\r\n");

    OSMOS::IO::Port::out((uint16_t) 0x3F8, "The block A now contains the following: ");
    str[0] = 'I';
    str[1] = 't';
    str[2] = '\'';
    str[3] = 's';
    str[4] = ' ';
    str[5] = 'a';
    str[6] = ' ';
    str[7] = 't';
    str[8] = 'e';
    str[9] = 's';
    str[10] = 't';
    str[11] = '\0';
    OSMOS::IO::Port::out((uint16_t) 0x3F8, str);
    OSMOS::IO::Port::out((uint16_t) 0x3F8, "\n\r");

    OSMOS::IO::Port::out((uint16_t) 0x3F8, "The block B now contains the following: ");
    dat[0] = 'H';
    dat[1] = 'e';
    dat[2] = 'l';
    dat[3] = 'l';
    dat[4] = 'o';
    dat[5] = '!';
    dat[6] = '\0';
    OSMOS::IO::Port::out((uint16_t) 0x3F8, dat);
    OSMOS::IO::Port::out((uint16_t) 0x3F8, "\n\r");

    OSMOS::System::Memory::freeBlock((address_t) str);
    OSMOS::System::Memory::freeBlock((address_t) dat);

    OSMOS::IO::Port::out((uint16_t) 0x3F8, "The block B now before after reallocation: ");
    OSMOS::IO::Port::out((uint16_t) 0x3F8, dat);
    dat = (char *) OSMOS::System::Memory::allocateBlock((address_t) dat);
    OSMOS::IO::Port::out((uint16_t) 0x3F8, "\n\r");
    OSMOS::IO::Port::out((uint16_t) 0x3F8, "The block B now contains after reallocation: ");
    dat[0] = 'H';
    dat[1] = 'a';
    dat[2] = 'l';
    dat[3] = 'l';
    dat[4] = 'o';
    dat[5] = '!';
    dat[6] = '\0';
    OSMOS::IO::Port::out((uint16_t) 0x3F8, dat);
    OSMOS::IO::Port::out((uint16_t) 0x3F8, "\n\r");
}
