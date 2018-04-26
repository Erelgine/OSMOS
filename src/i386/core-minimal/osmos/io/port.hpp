/*
 * The I/O port communication class
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

#ifndef PORT_HPP
#define PORT_HPP

#include "../osmos.hpp"

namespace OSMOS {
    namespace IO {
        /**
         * Port's class that contains functions for input/output
         * operations on the hardware
         */
        class Port {
        public:
        	/**
             * Receives a byte-sized value from port
             * @param port the port to communicate
             * @param value the value pointer to assign
             */
            static void in(uint16_t port, uint8_t *value);
            /**
             * Receives a word-sized value from port
             * @param port the port to communicate
             * @param value the value pointer to assign
             */
            static void in(uint16_t port, uint16_t *value);
            /**
             * Receives a double word-sized value from port
             * @param port the port to communicate
             * @param value the value pointer to assign
             */
            static void in(uint16_t port, uint32_t *value);
            
			/**
             * Sends a byte-sized value from port
             * @param port the port to communicate
             * @param value the value to send
             */
            static void out(uint16_t port, uint8_t value);
            /**
             * Sends a word-sized value from port
             * @param port the port to communicate
             * @param value the value to send
             */
            static void out(uint16_t port, uint16_t value);
			/**
             * Sends a double word-sized value from port
             * @param port the port to communicate
             * @param value the value to send
             */
            static void out(uint16_t port, uint32_t value);
        };
    };
};

#endif