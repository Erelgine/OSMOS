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
		public:
			/**
             * The <i>free</i> status indicates that the block is not used by the
             * kernel or userspace and can be allocated for code or data
             */
			static uint8_t BLOCK_STATUS_FREE;
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
             * The <i>invalid</i> type indicates that is the block is invalid and can
             * be allocated by the kernel or userspace
             */
			static uint8_t BLOCK_TYPE_INVALID;
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
                 * operation: (2 ^ <b>b</b>) + 6. The parenthesis is only to suppress
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
             * @param target
             * @param source
             * @param size
             */
			static void copy(uint8_t *target, uint8_t *source, uint32_t size);
            /**
             * Copies the memory from the source pointer to the target pointer
             * with the specified word-size
             * @param target
             * @param source
             * @param size
             */
			static void copy(uint16_t *target, uint16_t *source, uint32_t size);
            /**
             * Copies the memory from the source pointer to the target pointer
             * with the specified double word-size
             * @param target
             * @param source
             * @param size
             */
			static void copy(uint32_t *target, uint32_t *source, uint32_t size);
            /**
             * Copies the memory from the source pointer to the target pointer
             * with the specified quad word-size
             * @param target
             * @param source
             * @param size
             */
			static void copy(uint64_t *target, uint64_t *source, uint32_t size);
		};
	};
};

#endif