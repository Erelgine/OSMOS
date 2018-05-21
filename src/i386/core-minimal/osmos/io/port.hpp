/**
 * @file core-minimal/osmos/io/port.hpp
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

#ifndef PORT_HPP
#define PORT_HPP

#include "../osmos.hpp"

namespace OSMOS {
    namespace IO {
        /**
         * @namespace OSMOS::IO
         * @class Port
         * @brief The <code>Port</code> class is used for input/output operations on
         * devices present on a 16-bit range address called <code>port</code>. In order
         * to communicate with these ports, you need to use the <code>Port::in</code> and
         * <code>Port::out</code> functions:
         * <ul>
         *  <li><code>Port::in</code> allows reading a <code>value</code> from the
         *  specified <code>address</code>. The value is determined by the pointer and
         *  is altered by the received value.</li>
         *  <li><code>Port::out</code> allows writing a <code>value</code> from the
         *  specified <code>address</code>. The value is determined by the given
         *  argument and is not altered.</li>
         * </ul>
         * The most used port addresses is in the range from <code>0x000</code> to
         * <code>0x400</code>.
         **/
        class Port {
        private:
            /**
             * @name port
             * @brief The <code>port</code> value is an 16-bit unsigned integer (determined
             * by the port addressing system) that has a range of <code>0x0000</code> to
             * <code>0xFFFF</code>.
             */
            uint16_t port;

        public:
            /**
             * @name in
             * @brief <b>In</b>puts an 8-bit value from the specified <code>value</code> pointer,
             * in the specified 16-bit unsigned <code>port</code> value.
             * @param [in] port the port to communicate in the range of <code>0x0000</code> to
             * <code>0xFFFF</code>.
             * @param [in] value the 8-bit unsigned value pointer to assign
             **/
            static void in(uint16_t port, uint8_t *value);
            /**
             * @name in
             * @brief <b>In</b>puts an 16-bit value from the specified <code>value</code> pointer,
             * in the specified 16-bit unsigned <code>port</code> value.
             * @param [in] port the port to communicate in the range of <code>0x0000</code> to
             * <code>0xFFFF</code>.
             * @param [in] value the 16-bit unsigned value pointer to assign
             **/
            static void in(uint16_t port, uint16_t *value);
            /**
             * @name in
             * @brief <b>In</b>puts an 32-bit value from the specified <code>value</code> pointer,
             * in the specified 16-bit unsigned <code>port</code> value.
             * @param [in] port the port to communicate in the range of <code>0x0000</code> to
             * <code>0xFFFF</code>.
             * @param [in] value the 32-bit unsigned value pointer to assign
             **/
            static void in(uint16_t port, uint32_t *value);
            /**
             * @name in
             * @brief <b>In</b>puts an ASCII formatted string from the specified <code>str</code>
             * pointer. The given <code>str</code> value ends with a <code>NULL</code> (<code>\0</code>)
             * terminating value.
             * @param [in] port the port to communicate in the range of <code>0x0000</code> to
             * <code>0xFFFF</code>.
             * @param [in] value the ASCII string value pointer to assign
             **/
            static void in(uint16_t port, char *str);

            /**
             * @name out
             * @brief <b>Out</b>puts an 8-bit value from the specified <code>value</code>,
             * in the specified 16-bit unsigned <code>port</code> value.
             * @param [in] port the port to communicate in the range of <code>0x0000</code> to
             * <code>0xFFFF</code>.
             * @param [in] value the 8-bit unsigned value pointer to send
             **/
            static void out(uint16_t port, uint8_t value);
            /**
             * @name out
             * @brief <b>Out</b>puts an 16-bit value from the specified <code>value</code>,
             * in the specified 16-bit unsigned <code>port</code> value.
             * @param [in] port the port to communicate in the range of <code>0x0000</code> to
             * <code>0xFFFF</code>.
             * @param [in] value the 16-bit unsigned value pointer to send
             **/
            static void out(uint16_t port, uint16_t value);
            /**
             * @name out
             * @brief <b>Out</b>puts an 32-bit value from the specified <code>value</code>,
             * in the specified 16-bit unsigned <code>port</code> value.
             * @param [in] port the port to communicate in the range of <code>0x0000</code> to
             * <code>0xFFFF</code>.
             * @param [in] value the 32-bit unsigned value pointer to send
             **/
            static void out(uint16_t port, uint32_t value);
            /**
             * @name out
             * @brief <b>Out</b>puts an ASCII formatted string from the specified <code>str</code>
             * pointer. The given <code>str</code> value should ends with a <code>NULL</code>
             * (<code>\0</code>) terminating value.
             * @param [in] port the port to communicate in the range of <code>0x0000</code> to
             * <code>0xFFFF</code>.
             * @param [in] value the ASCII string value pointer to send
             **/
            static void out(uint16_t port, const char *str);

            /**
             * @name Port
             * @brief Creates an <code>Port</code> object, with the specified <code>port</code> to
             * communicate from. This suppress the <code>port</code> argument, and can be useful if
             * multiple accesses to the same <code>port</code> occurs.
             * @param port the 16-bit unsigned integer <code>port</code> to communicate from
             **/
            Port(uint16_t port);
            /**
             * @name getPortAddress
             * @brief Gets the address port set from the <code>Port::Port</code> constructor with the
             * <code>port</code> argument.
             * @return the address of the port in the range of <code>0x0000</code> <code>0xFFFF</code>
             **/
            uint16_t getPortAddress();

            /**
             * @name in
             * @brief <b>In</b>puts an 8-bit value from the specified <code>value</code> pointer,
             * in the specified 16-bit unsigned <code>port</code> value from the constructor.
             * @param [in] value the 8-bit unsigned value pointer to assign
             **/
            void in(uint8_t *value);
            /**
             * @name in
             * @brief <b>In</b>puts an 16-bit value from the specified <code>value</code> pointer,
             * in the specified 16-bit unsigned <code>port</code> value from the constructor.
             * @param [in] value the 16-bit unsigned value pointer to assign
             **/
            void in(uint16_t *value);
            /**
             * @name in
             * @brief <b>In</b>puts an 32-bit value from the specified <code>value</code> pointer,
             * in the specified 16-bit unsigned <code>port</code> value from the constructor.
             * @param [in] value the 32-bit unsigned value pointer to assign
             **/
            void in(uint32_t *value);
            /**
             * @name in
             * @brief <b>In</b>puts an ASCII formatted string from the specified <code>str</code>
             * pointer. The given <code>str</code> value ends with a <code>NULL</code> (<code>\0</code>)
             * terminating value.
             * @param [in] str the ASCII value pointer to assign
             **/
            void in(char *str);

            /**
             * @name out
             * @brief <b>Out</b>puts an 8-bit value from the specified <code>value</code>,
             * in the specified 16-bit unsigned <code>port</code> value from the constructor.
             * @param [in] value the 8-bit unsigned value pointer to send
             **/
            void out(uint8_t value);
            /**
             * @name out
             * @brief <b>Out</b>puts an 16-bit value from the specified <code>value</code>,
             * in the specified 16-bit unsigned <code>port</code> value from the constructor.
             * @param [in] value the 16-bit unsigned value pointer to send
             **/
            void out(uint16_t value);
            /**
             * @name out
             * @brief <b>Out</b>puts an 32-bit value from the specified <code>value</code>,
             * in the specified 16-bit unsigned <code>port</code> value from the constructor.
             * @param [in] value the 32-bit unsigned value pointer to send
             **/
            void out(uint32_t value);
            /**
             * @name out
             * @brief <b>Out</b>puts an ASCII formatted string from the specified <code>str</code>
             * pointer. The given <code>str</code> value should ends with a <code>NULL</code>
             * (<code>\0</code>) terminating value.
             * @param [in] value the ASCII string value pointer to send
             **/
            void out(const char *str);
        };
    };
};

#endif