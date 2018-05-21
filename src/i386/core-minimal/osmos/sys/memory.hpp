/**
 * @file core-minimal/osmos/sys/memory.hpp
 * @brief The main header for the Memory class
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

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <stddef.h>
#include "../osmos.hpp"

namespace OSMOS {
    namespace System {
        /**
         * @namespace OSMOS::System
         * @name Memory
         * @brief The <code>Memory</code> namespace contains memory access
         */
        namespace Memory {
            /**
             * @brief The Access class, which contains functions for memory manipulation
             * such as filling and copying
             **/
            class Access {
            public:
                /**
                 * @brief Fills the memory from the specified pointer to the specified size
                 * with a byte-sized value
                 * @param ptr the pointer to the memory to fill
                 * @param size the size to fill
                 * @param val the value to fill
                 */
                static void fill(void *ptr, size_t size, uint8_t val);

                /**
                 * @brief Copies the memory from the source pointer to the target pointer
                 * with the specified byte-size
                 * @param target the target to paste from
                 * @param source the source to copy from
                 * @param size the size to copy
                 */
                static void copy(void *target, void *source, size_t size);
            };

            /**
             * @brief The Management class, which the contains memory allocation engine,
             * the Frame structure and the Block structure
             **/
            class Management {
            public:
                class Area {
                public:
                    /**
                     * @brief The lower address of the allocation area. See the public
                     * function <i>Management::setArea(...)</i> in order to alter the
                     * private values
                     **/
                    static size_t LOWER_ADDRESS;
                    /**
                     * @brief The upper address of the allocation area. See the public
                     * function <i>Management::setArea(...)</i> in order to alter the
                     * private values
                     **/
                    static size_t UPPER_ADDRESS;

                    /**
                     * @brief Gets the memory allocation area
                     * @param lowerAddress the start point of the memory allocation area
                     * @param upperAddress the end point of the memory allocation area
                     **/
                    static void getArea(size_t *lowerAddress, size_t *upperAddress);
                    /**
                     * @brief Sets the memory allocation area
                     * @param lowerAddress the start point of the memory allocation area
                     * @param upperAddress the end point of the memory allocation area
                     **/
                    static void setArea(size_t lowerAddress, size_t upperAddress);

                    /**
                     * @brief Gets the number of allocated blocks.
                     * @return the number of allocated blocks
                     **/
                    static uint64_t getAllocatedCount();
                    /**
                     * @brief Gets the size of all allocated blocks.
                     * @return the size of all allocated blocks
                     **/
                    static uint64_t getAllocatedSize();
                };


                /**
                 * @brief The magic value of the block, to check if the block is valid.
                 * The <i>Block->magic</i> field should be always of this constant value
                 **/
                static const uint16_t BLOCK_MAGIC_VALUE;

                /**
                 * @brief The Block structure, describes the size and allocation status
                 * of the block
                 **/
                struct Block {
                    /**
                     * @brief The magic field, to check if the block is valid or not.
                     * Compare this field with the static constant value in the same
                     * class
                     **/
                    uint16_t magic;
                    /**
                     * @brief The size field, which indicates the size of the allocated
                     * block
                     **/
                    uint64_t size;
                    /**
                     * @brief The allocation state field, which indicates if the block
                     * is allocated. Before checking this value, 
                     **/
                    bool isAllocated;
                } __attribute__((packed));

                /**
                 * @brief Checks if the specified block is valid and allocated.
                 * @param block the block to check
                 * @return the allocation status of the block
                 **/
                static bool isBlockAllocated(OSMOS::System::Memory::Management::Block *block);

                /**
                 * @brief Finds an available or allocated block at the specified starting
                 * address using
                 **/
                static size_t findBlock(size_t startAddress, bool allocated, uint64_t size);
                /**
                 * @brief Finds an available or allocated block at the specified starting
                 * address
                 **/
                static size_t findBlock(size_t startAddress, bool allocated);

                /**
                 * @brief Allocates a new available block from the allocation area.
                 * @param size the size to allocate
                 * @return the address of the block data section
                 **/
                static size_t allocateBlock(uint64_t size);
                /**
                 * @brief Deallocates an allocated block from it's specified address
                 * @param address the address of the block
                 * @param size the size of the block (less will just fill until size)
                 * @return the status of the deallocation
                 **/
                static bool deallocateBlock(size_t address, uint64_t size);
            };
        };
    };
};

/**
 * The following is the most needed part of the entire core-minimal and core-base kernel.
 * It permits the creation and destroy of objects, which is mandatory for a C++ kernel.
 **/

void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *pointer);
void operator delete[](void *pointer);
void operator delete(void *pointer, size_t size);
void operator delete[](void *pointer, size_t size);

#endif