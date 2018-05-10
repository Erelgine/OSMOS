/**
 * @file core-minimal/osmos/io/port.cpp
 * @brief The main code for the Port class
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

#include "port.hpp"

#include "../osmos.hpp"

void OSMOS::IO::Port::in(uint16_t port, uint8_t *value) {
    asm("inb ebx, %[port]\n \
         mov %[value], ebx"
       : [value] "=a" (value)
       : [port] "c" (port));
}

void OSMOS::IO::Port::in(uint16_t port, uint16_t *value) {
    asm("inw bx, %[port]\n \
         mov %[value], bx"
       : [value] "=a" (value)
       : [port] "c" (port));
}

void OSMOS::IO::Port::in(uint16_t port, uint32_t *value) {
    asm("ind bl, %[port]\n \
         mov %[value], bl"
       : [value] "=a" (value)
       : [port] "c" (port));
}

void OSMOS::IO::Port::in(uint16_t port, char *str) {
    uint8_t character = 0xFF;

    for (int i = 0; character != 0; i++) {
        OSMOS::IO::Port::in(port, &character);

        if (character == 0)
            break;
        else
            str[i] = character;
    }
}

void OSMOS::IO::Port::out(uint16_t port, uint8_t value) {
    asm("outb %[port], %[value]"
       :
       : [port] "d" (port), [value] "a" (value));
}

void OSMOS::IO::Port::out(uint16_t port, uint16_t value) {
    asm("outw %[port], %[value]"
       :
       : [port] "d" (port), [value] "a" (value));    
}
void OSMOS::IO::Port::out(uint16_t port, uint32_t value) {
    asm("outd %[port], %[value]"
       :
       : [port] "d" (port), [value] "a" (value));
}

void OSMOS::IO::Port::out(uint16_t port, const char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        OSMOS::IO::Port::out(port, (uint8_t) str[i]);
}

OSMOS::IO::Port::Port(uint16_t port) {
    this->port = port;
}

uint16_t OSMOS::IO::Port::getPortAddress() {
    return this->port;
}

void OSMOS::IO::Port::in(uint8_t *value) {
    OSMOS::IO::Port::in(this->port, value);
}

void OSMOS::IO::Port::in(uint16_t *value) {
    OSMOS::IO::Port::in(this->port, value);
}

void OSMOS::IO::Port::in(uint32_t *value) {
    OSMOS::IO::Port::in(this->port, value);
}

void OSMOS::IO::Port::in(char *str) {
    OSMOS::IO::Port::in(this->port, str);
}

void OSMOS::IO::Port::out(uint8_t value) {
    OSMOS::IO::Port::out(this->port, value);
}

void OSMOS::IO::Port::out(uint16_t value) {
    OSMOS::IO::Port::out(this->port, value);
}

void OSMOS::IO::Port::out(uint32_t value) {
    OSMOS::IO::Port::out(this->port, value);
}

void OSMOS::IO::Port::out(const char *str) {
    OSMOS::IO::Port::out(this->port, str);
}