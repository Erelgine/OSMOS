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

    //OSMOS::IO::SerialPort *debug = new OSMOS::IO::SerialPort(OSMOS::IO::SerialPort::COMMUNICATION_PORT_1);
    //debug->out("Hello, this is a test message !");

    OSMOS::IO::Port::out((uint16_t) OSMOS::IO::SerialPort::COMMUNICATION_PORT_1 + 1, (uint8_t) 0x00);
	OSMOS::IO::Port::out((uint16_t) OSMOS::IO::SerialPort::COMMUNICATION_PORT_1 + 3, (uint8_t) 0x80); /* Enable divisor mode */
	OSMOS::IO::Port::out((uint16_t) OSMOS::IO::SerialPort::COMMUNICATION_PORT_1 + 0, (uint8_t) 0x03); /* Div Low:  03 Set the port to 38400 bps */
	OSMOS::IO::Port::out((uint16_t) OSMOS::IO::SerialPort::COMMUNICATION_PORT_1 + 1, (uint8_t) 0x00); /* Div High: 00 */
	OSMOS::IO::Port::out((uint16_t) OSMOS::IO::SerialPort::COMMUNICATION_PORT_1 + 3, (uint8_t) 0x03);
	OSMOS::IO::Port::out((uint16_t) OSMOS::IO::SerialPort::COMMUNICATION_PORT_1 + 2, (uint8_t) 0xC7);
	OSMOS::IO::Port::out((uint16_t) OSMOS::IO::SerialPort::COMMUNICATION_PORT_1 + 4, (uint8_t) 0x0B);
    
    OSMOS::IO::Port::out((uint16_t) OSMOS::IO::SerialPort::COMMUNICATION_PORT_1, "POURQUOI CA MARCHE PAS... !!!");

    uint16_t *screen = (uint16_t *) 0xB8000;
    screen[0] = 0xF040;
}
