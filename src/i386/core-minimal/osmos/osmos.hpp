/**
 * @file core-minimal/osmos/osmos.hpp
 * @author Alexis BELMONTE
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

#ifndef OSMOS_HPP
#define OSMOS_HPP

/**
 * @name uint8_t
 * @brief The 8-bit wide unsigned integer is the smallest unit of data that x86 processors
 * and compatible can support. Called as a <code>byte</code>; or an unsigned character because
 * of the ASCII character size of 8 bits, or eight binary values. The most common usage for this
 * type is as mentioned earlier is for the ASCII character table. Most old operating systems use
 * commonly this size representation to display characters to the VGA text-mode graphics. The
 * range that the type can support is of 0 to 255 (<code>2 ^ 8</code>)
 **/
typedef unsigned char                    uint8_t;
/**
 * @name uint16_t
 * @brief The 16-bit wide unsigned integer is the result of combining two <code>byte</code>s.
 * Called as a <code>word</code>, or an unsigned short. It is used commonly in <i>Real mode</i>;
 * because of it's 16-bit limit. The range that the type can support is of 0 to 65536
 * (<code>2 ^ 16</code>)
 **/
typedef unsigned short                   uint16_t;
/**
 * @name uint32_t
 * @brief The 32-bit wide unsigned integer is the result of combining two <code>word</code>s.
 * Called as a <code>dword</code> (<b>d</b>ouble <b>word</b>), or an unsigned int. It is the
 * most used data type for all kinds of operations such as memory addressing, counting and
 * checksum calculation; and is supported by i386 or compatible processors and AMD64 compatible
 * processors, even if it's native addressing is of 64-bit
 */
typedef unsigned int                     uint32_t;
/**
 * @name uint64_t
 * @brief The 64-bit wide unsigned integer is the result of combining two <code>dword</code>s.
 * Called as a <code>qword</code> (<b>q</b>wad <b>word</b>), or an unsigned long. It is the
 * most used data type for the AMD64 generations of processors, because of it's native 64-bit
 * support. i386 processors and compatible can still support this value by using two 32-bit
 * registers.
 */
typedef unsigned long                    uint64_t;

/**
 * @name int8_t
 * @brief The 8-bit wide signed integer is the result of using an 8-bit wide unsigned integer
 * but with a minor modification: using the 8th byte for the sign (positive or negative).
 */
typedef signed char                      int8_t;
/**
 * @name int16_t
 * @brief The 16-bit wide signed integer is the same operation done on a 8-bit wide signed
 * integer, but instead using the 16th byte for the sign.
 **/
typedef signed short                     int16_t;
/**
 * @name int32_t
 * @brief The 32-bit wide signed integer is the same operation done on a 16-bit wide signed
 * integer, but instead using the 32nd byte for the sign.
 **/
typedef signed int                       int32_t;
/**
 * @name int64_t
 * @brief The 64-bit wide signed integer is the same operation done on a 32-bit wide signed
 * integer, but instead using the 64th byte for the sign.
 **/
typedef signed long                      int64_t;

// Processor specific address size
/**
 * @name size_t
 * @brief This type definition is depending on the processor's architecture. It represents the
 * processor's native unsigned integer size. For example, an i386 compatible processor will have
 * a 32-bit wide unsigned integer in it's <code>size_t</code> definition, while the AMD64 range of
 * processors will have a 64-bit wide unsigned integer.
 **/
typedef uint32_t                         size_t;

// The null definition, which is essential for a lot of things
#ifdef NULL
    #undef NULL
#endif
#define NULL                             0

// All namespaces comments should be defined here
/**
 * @name OSMOS
 * @brief The <code>OSMOS</code> namespace, containing the main framework of the kernel.
 * You can access to sub-namespaces from this namespace that can interact with
 * the components of the computer such as the serial port and the PCI cards installed
 * on the computer from the <code>IO</code> sub-namespace.
 **/
namespace OSMOS {
    /**
     * @brief The <code>System</code> namespace allows you to control the most essential
     * parts of a computer, such as the present memory (from the <code>Memory</code>
     * sub-namespace).
     **/
    namespace System {
        
    };
    
    /**
     * @brief The <code>IO</code> namespace allows you to communicate with the parts
     * of a computer such as the PCI (Peripheral Component Interconnect), and graphics.
     **/
    namespace IO {
        
    };
};

#endif