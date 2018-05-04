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
         * @brief Port's class that contains functions for input/output
         * operations on the hardware
         **/
        class Port {
        public:
            /**
             * @brief Receives a byte-sized value from the specified
             * port
             * @param port the port to communicate
             * @param value the value pointer to assign
             **/
            static void in(uint16_t port, uint8_t *value);
            /**
             * @brief Receives a word-sized value from the specified
             * port
             * @param port the port to communicate
             * @param value the value pointer to assign
             **/
            static void in(uint16_t port, uint16_t *value);
            /**
             * @brief Receives a double word-sized value from the
             * specified port
             * @param port the port to communicate
             * @param value the value pointer to assign
             **/
            static void in(uint16_t port, uint32_t *value);
            /**
             * @brief Receives a string terminating with the character \0
             * from the specified port
             * @param port the port to communicate
             * @param str the string to read
             **/
            static void in(uint16_t port, char *str);
            
            /**
             * @brief Sends a byte-sized value from the specified port
             * @param port the port to communicate
             * @param value the value to send
             **/
            static void out(uint16_t port, uint8_t value);
            /**
             * @brief Sends a word-sized value from the specified port
             * @param port the port to communicate
             * @param value the value to send
             **/
            static void out(uint16_t port, uint16_t value);
            /**
             * @brief Sends a double word-sized value from the specified port
             * @param port the port to communicate
             * @param value the value to send
             **/
            static void out(uint16_t port, uint32_t value);
            /**
             * @brief Sends a string from the specified port
             * @param port the port to communicate
             * @param str the string to send
             **/
            static void out(uint16_t port, const char *str);
        };
    };
};

#endif