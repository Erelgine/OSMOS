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

extern "C"
void kboot(uint32_t magic, uint32_t table_address) {
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 1, (uint8_t) 0x00);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 3, (uint8_t) 0x80);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 0, (uint8_t) 0x03);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 1, (uint8_t) 0x00);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 3, (uint8_t) 0x03);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 2, (uint8_t) 0xC7);
    OSMOS::IO::Port::out((uint16_t) 0x3F8 + 4, (uint8_t) 0x0B);

    OSMOS::IO::Port::out((uint16_t) 0x3F8, (uint8_t) 'H');
    OSMOS::IO::Port::out((uint16_t) 0x3F8, (uint8_t) 'i');
    OSMOS::IO::Port::out((uint16_t) 0x3F8, (uint8_t) '!');
    OSMOS::IO::Port::out((uint16_t) 0x3F8, (uint8_t) '\n');
    OSMOS::IO::Port::out((uint16_t) 0x3F8, (uint8_t) '\r');    
}
