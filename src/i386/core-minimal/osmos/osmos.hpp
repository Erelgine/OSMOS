/**
 * @file core-minimal/osmos/osmos.hpp
 * @brief The main header of the core-minimal kernel
 **/

/*
 * The OSMOS header
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

#ifndef OSMOS_HPP
#define OSMOS_HPP

// Global type definitions
typedef unsigned char                    uint8_t;
typedef unsigned short                   uint16_t;
typedef unsigned int                     uint32_t;
typedef unsigned long                    uint64_t;

typedef signed char                      int8_t;
typedef signed short                     int16_t;
typedef signed int                       int32_t;
typedef signed long                      int64_t;

// Processor specific address size
typedef uint32_t                         address_t;

// Highest number the processor can handle natively
#define MAX_INTEGER                      2 ^ 32

// The null definition, which is essential for a lot of things
#ifdef NULL
    #undef NULL
#endif
#define NULL                             0

// All namespaces comments should be defined here
/**
 * The main namespace for the entire operating system which allows you to
 * access and control the computer
 **/
namespace OSMOS {
    /**
     * @brief The System namespace allows you to control the most essential parts of
     * a computer
     **/
    namespace System {
        
    };
    
    /**
     * @brief The IO (Input/Output) namespace allows you to communicate with the
     * parts of a computer such as PCI (Peripheral Component Interconnect),
     * and display
     **/
    namespace IO {
        
    };
};

#endif