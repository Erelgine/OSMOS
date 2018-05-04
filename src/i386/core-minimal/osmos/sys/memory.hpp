/*
 * The memory allocation class
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

#include "../osmos.hpp"

namespace OSMOS {
    namespace System {
        /**
         * The Memory class, which contains controls for easy memory
         * manipulation such as filling, copying. It also contains memory
         * allocation functions which permits the usage of <b>new</b> and
         * <b>delete<b> for variables and arrays
         */
        class Memory {
        private:
            /**
             * The base address of the memory block allocation frame
             */
            static address_t BLOCK_BASE_ADDRESS;
            /**
             * The limit address of the memory block allocation frame
             */
            static address_t BLOCK_LIMIT_ADDRESS;
            
        public:
            /**
             * Initializes the Memory class
             */
            static void initialize();
            
            /**
             * The <i>used</i> status indicates that the block is used by the kernel
             * or userspace and cannot be allocated, unless it is freed
             */
            static uint8_t BLOCK_STATUS_USED;
            /**
             * The <i>reserved</i> status indicates that the block is reserved by
             * the kernel (reserving for the userspace is denied) and cannot be
             * freed or allocated by the kernel or userspace
             */
            static uint8_t BLOCK_STATUS_RESERVED;

            /**
             * The <i>data</i> type indicates that the block contains only data that
             * cannot be executed by the processor
             */
            static uint8_t BLOCK_TYPE_DATA;
            /**
             * The <i>code</i> type indicates that the block contains only readable
             * code that can be executed by the processor
             */
            static uint8_t BLOCK_TYPE_CODE;
            
            /**
             * The <i>magic</i> value to check first when you access a block. Compare
             * this value with the value of your current structure to be sure this is
             * a valid structure; but it is more recommended that you use the function
             * isBlockValid in order to check accuratly if the structure is valid Block
             */
            static uint16_t BLOCK_MAGIC_VALUE;

            /**
             * The Block header, which is placed before the actual data stored
             * inside
             */
            struct Block {
                /**
                 * The <i>magic</i> field, which always holds the value <u>0xB6A0</u>
                 * and indicates that the block is valid. If the magic header
                 * is not the following value, the kernel considerates that the
                 * block is available for allocation by the kernel or userspace
                 */
                uint16_t magic; 
                /**
                 * The <i>flags</i> field, which holds both the status and the type of
                 * the block. If you want to compare them, an <b>and</b> bitwise
                 * operation is recommended, but compare only a value one by one or
                 * you may not obtain what you expect
                 */
                uint8_t flags:4;
                /**
                 * The <i>size</i> field, which holds the size virtually. If you want
                 * to get the real block size in bytes, you need to do the following
                 * operation: 2 ^ (<b>size</b> + 6). The parenthesis is only to suppress
                 * the compiler's warning
                 */
                uint8_t size;
            } __attribute__((packed));

            /**
             * Fills the memory from the specified pointer to the specified size
             * with a byte-sized value
             * @param ptr the pointer to the memory to fill
             * @param size the size to fill
             * @param val the value to fill
             */
            static void fill(uint8_t *ptr, uint32_t size, uint8_t val);
            /**
             * Fills the memory from the specified pointer to the specified size
             * with a word-sized value
             * @param ptr the pointer to the memory to fill
             * @param size the size to fill
             * @param val the value to fill
             */
            static void fill(uint16_t *ptr, uint32_t size, uint16_t val);
            /**
             * Fills the memory from the specified pointer to the specified size
             * with a double word-sized value
             * @param ptr the pointer to the memory to fill
             * @param size the size to fill
             * @param val the value to fill
             */
            static void fill(uint32_t *ptr, uint32_t size, uint32_t val);
            /**
             * Fills the memory from the specified pointer to the specified size
             * with a quad word-sized value
             * @param ptr the pointer to the memory to fill
             * @param size the size to fill
             * @param val the value to fill
             */
            static void fill(uint64_t *ptr, uint32_t size, uint64_t val);

            /**
             * Copies the memory from the source pointer to the target pointer
             * with the specified byte-size
             * @param target the target to paste from
             * @param source the source to copy from
             * @param size the size to copy
             */
            static void copy(uint8_t *target, uint8_t *source, uint32_t size);
            /**
             * Copies the memory from the source pointer to the target pointer
             * with the specified word-size
             * @param target the target to paste from
             * @param source the source to copy from
             * @param size the size to copy
             */
            static void copy(uint16_t *target, uint16_t *source, uint32_t size);
            /**
             * Copies the memory from the source pointer to the target pointer
             * with the specified double word-size
             * @param target the target to paste from
             * @param source the source to copy from
             * @param size the size to copy
             */
            static void copy(uint32_t *target, uint32_t *source, uint32_t size);
            /**
             * Copies the memory from the source pointer to the target pointer
             * with the specified quad word-size
             * @param target the target to paste from
             * @param source the source to copy from
             * @param size the size to copy
             */
            static void copy(uint64_t *target, uint64_t *source, uint32_t size);

            /**
             * Sets the base address of the memory allocation frame
             * @param address the base address of the memory allocation frame
             **/
            static void setBaseAddress(address_t address);

            /**
             * Sets the limit address of the memory allocation frame
             * @param address the base address of the memory allocation frame
             **/
            static void setLimitAddress(address_t address);
            
            /**
             * Gets the base address of the memory allocation frame
             * @return the base address of the memory allocation frame
             **/
            static address_t getBaseAddress();

            /**
             * Gets the limit address of the memory allocation frame
             * @return the base address of the memory allocation frame
             **/
            static address_t getLimitAddress();
            
            /**
             * Checks the given block if it is valid
             * @param block the block to check
             * @return a positive value if the block is valid or a negative
             * value if the block is bad or unallocated
             */
            static bool isValid(OSMOS::System::Memory::Block *block);
            /**
             * Checks the given block if it is allocated or not
             * @param block the block to check
             * @return a positive value if the block is allocated or a negative
             * value if the block is freed
             */
            static bool isAllocated(OSMOS::System::Memory::Block *block);
            /**
             * Checks the given block if it is reserved or not by the kernel
             * @param block the block to check
             * @return a positive value if the block is reserved by the kernel
             * or a negative value is the block is not reserved by the kernel
             */
            static bool isReserved(OSMOS::System::Memory::Block *block);
            /**
             * Checks the given block if it contains data
             * @param block the block to check
             * @return a positive value if the block contains data or a
             * negative value if the block contains other than data
             */
            static bool isData(OSMOS::System::Memory::Block *block);
            /**
             * Checks the given block if it contains code
             * @param block the block to check
             * @return a positive value if the block contains code or a
             * negative value if the block contains other than code
             */
            static bool isCode(OSMOS::System::Memory::Block *block);
            
            /**
             * Gets the size of the block
             * @param block the block to access
             * @return the size in bytes of the block
             **/
            static uint64_t getBlockSize(OSMOS::System::Memory::Block *block);
            /**
             * Gets the size of the given block
             * @param block the block to access
             * @return the size in bytes of the block
             */
            static uint64_t getSize(OSMOS::System::Memory::Block *block);

            /**
             * Finds an available block for allocation
             * @param start the address to start from
             * @param size the available size to obtain
             * @return the address of the available block
             */
            static address_t findAvailableBlock(address_t start, uint64_t size);
            /**
             * Finds an available block for allocation
             * @param size the size
             * @return the address of the available block
             **/
            static address_t findAvailableBlock(uint64_t size);
            /**
             * Finds an allocated block
             * @param start the address to start from
             * @return the address of the allocated block
             **/
            static address_t findAllocatedBlock(address_t start);
            /**
             * Finds an block from it's encapsulated pointer
             * @param pointer the encapsulated pointer to find from
             * @return the address of the allocated block
             **/
            static address_t findBlock(address_t pointer);
            /**
             * Finds an available block for use and allocate it
             * @param size the size of the block to allocate
             * @param flags the flags/properties to set for the block
             * @return the address of the block's actual data access section
             **/
            static address_t allocateBlock(address_t size, uint8_t flags);
            /**
             * Finds an available block for use and allocate it
             * @param size the size of the block to allocate
             * @return the address of the block's actual data access section
             **/
            static address_t allocateBlock(address_t size);
            /**
             * Frees a block and mark it as available
             * @param block the block to free
             **/
            static void freeBlock(OSMOS::System::Memory::Block *block);
            /**
             * Frees a block from it's encapsulated pointer and mark it as available
             * @param pointer the pointer encapsulated by the block
             **/
            static void freeBlock(address_t pointer);
        };
    };
};

#endif