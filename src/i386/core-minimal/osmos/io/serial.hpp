/**
 * @file core-minimal/osmos/io/serial.hpp
 * @brief The main header for the SerialPort class
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

namespace OSMOS {
    namespace IO {
        /**
         * @brief The SerialPort class, which allows communication over
         * a serial port
         **/
        class SerialPort {
        private:
            /**
             * @brief The port address of the serial port
             **/
            uint16_t portAddress;
            /**
             * @brief The actual port object for input/output communication
             **/
            OSMOS::IO::Port *port;

            /**
             * @brief The real constructor which setups the object
             * @param address the address port to communicate
             * @param baudrate the speed of the communication
             * @param wLength the word length of the communication
             * @param parity the parity of the communication
             **/
            void setup(uint16_t address, uint32_t baudrate, uint8_t wLength, uint8_t parity);

        public:
            /**
             * @brief The first communication port, also called <i>COM1</i>,
             * which holds the value 0x3F8
             **/
            static const uint16_t COMMUNICATION_PORT_1;
            /**
             * @brief The second communication port, also called <i>COM2</i>,
             * which holds the value 0x2F8
             **/
            static const uint16_t COMMUNICATION_PORT_2;
            /**
             * @brief The third communication port, also called <i>COM3</i>,
             * which holds the value 0x3E8
             **/
            static const uint16_t COMMUNICATION_PORT_3;
            /**
             * @brief The fourth communication port, also called <i>COM4</i>,
             * which holds the value 0x2E8
             **/
            static const uint16_t COMMUNICATION_PORT_4;

            /**
             * @brief The FIFO status <i>NOT_AVAILABLE</i> for the Interrupt
             * Identification Register indicates that the FIFO is not available
             * on the chip
             **/
            static const uint8_t FIFO_NOT_AVAILABLE;
            /**
             * @brief The FIFO status <i>RESERVED_CONDITION</i> for the Interrupt
             * Indentification Register indicates that the FIFO needs a reserved
             * condition in order to work
             **/
            static const uint8_t FIFO_RESERVED_CONDITION;
            /**
             * @brief The FIFO status <i>ENABLED_OFF</i> for the Interrupt Identification
             * Register indicates that the FIFO is present but is not functionning
             **/
            static const uint8_t FIFO_ENABLED_OFF;
            /**
             * @brief The FIFO status <i>ENABLED</i> for the Interrupt Identification
             * Register indicates that the FIFO is present and functionning
             **/
            static const uint8_t FIFO_ENABLED;

            /**
             * @brief The Modem Status Interrupt for the Interrupt Indentification
             * Register indicates that an Modem Status Change interrupt has been called
             **/
            static const uint8_t IIRSTATUS_MODEM_STATUS_INTERRUPT;
            /**
             * @brief The Transmitter Holding Register Empty Interrupt for the Interrupt
             * Identification Register indicates that an Transmitter Holding Register
             * Empty Interrupt has been called
             **/
            static const uint8_t IIRSTATUS_EMPTY_THR_INTERRUPT;
            /**
             * @brief The Received Data Available Interrupt for the Interrupt Identification
             * Register indicates that an Received Data Available Interrupt has been called
             **/
            static const uint8_t IIRSTATUS_RECEIVED_DATA_AVAILABLE_INTERRUPT;
            /**
             * @brief The Receiver Line Status Interrupt for the Interrupt Identification
             * Register indicates that an Receiver Line Status Interrupt has been called
             **/
            static const uint8_t IIRSTATUS_RECEIVER_LINE_STATUS_INTERRUPT;
            /**
             * @brief The Time-out Interrupt Pending for the Interrupt Indentification
             * Register indicates that an interrupt is called but is not assigned
             **/
            static const uint8_t IIRSTATUS_TIMEOUT_INTERRUPT_PENDING;

            /**
             * @brief The word length of the line would be of 5 bits. No letters can be sent
             * or received off.
             **/
            static const uint8_t LCR_WORDLENGTH_5BITS;
            /**
             * @brief The word length of the line would be of 6 bits. Digits and characters
             * can be sent or received off.
             **/
            static const uint8_t LCR_WORDLENGTH_6BITS;
            /**
             * @brief The word length of the line would be of 7 bits. Digits, letters without
             * accentuation and characters can be sent or received off.
             **/
            static const uint8_t LCR_WORDLENGTH_7BITS;
            /**
             * @brief The word length of the line would be of 8 bits. Digits, letters with
             * accentuation and characters can be sent or received off.
             **/
            static const uint8_t LCR_WORDLENGTH_8BITS;

            /**
             * @brief The parity of the line would be none, which increases speed but also
             * has more chances that you get corrupt data
             **/
            static const uint8_t LCR_PARITY_NONE;
            /**
             * @brief The parity of the line would be odd, which means that each bit in the
             * word is added as a simple count of the number of logical positive bits. If
             * this is an odd number of bits, the parity bit will be transmitted as a logical
             * negative bit, or a positive bit if the count is even
             **/
            static const uint8_t LCR_PARITY_ODD;
            /**
             * @brief The parity of the line would be even, which is the same operation as
             * <i>LCR_PARITY_ODD</i>, but if the number of bits is an odd number, it will be
             * transmitted as a positive bit; which is doing the opposite
             **/
            static const uint8_t LCR_PARITY_EVEN;
            /**
             * @brief The parity of the line would be mark, which means that the parity bit
             * will always be positive
             **/
            static const uint8_t LCR_PARITY_MARK;
            /**
             * @brief The parity of the line would be mark, which means that the parity bit
             * will always be negative
             **/
            static const uint8_t LCR_PARITY_SPACE;

            /**
             * @brief The stop bit of the line would be of one bit
             **/
            static const bool ONE_STOP_BIT;
            /**
             * @brief The stop bit of the line would be of one and a half bit
             **/
            static const bool ONE_HALF_STOP_BIT;

            /**
             * @brief The Interrupt Enable Register allows enabling and/or
             * disabling interrupts such as the Low Power Mode or the
             * Sleep Mode
             **/
            struct InterruptEnableRegister {
                /**
                 * @brief The Low Power Mode which is used only with a 16750
                 * or compatible chip, allows you to control if the chip needs
                 * to reduce it's power consumption
                 **/
                bool lowPowerMode;
                /**
                 * @brief The Sleep Mode which is used only with a 16750 or
                 * compatible chip, allows you to control if the chip needs to
                 * switch into sleep mode
                 **/
                bool sleepMode;
                /**
                 * @brief The Modem Status Interrupt is used to notify when
                 * the modem has changed or altered it's state or settings
                 **/
                bool msInterrupt;
                /**
                 * @brief The Receiver Line Status Interrupt indicates that
                 * a/some bit(s) have been altered in the Line Status Register
                 **/
                bool rsInterrupt;
                /**
                 * @brief The Transmitter Holding Register Empty Interrupt allows
                 * you to know that the output buffer has finished sending data
                 * that is pushed into the buffer
                 **/
                bool threiInterrupt;
                /**
                 * @brief The Received Data Interrupt permits the knowledge of
                 * receiving data waiting to be read
                 **/
                bool rdaInterrupt;
            };

            /**
             * @brief The Interrupt Identification Register allows the identification
             * of the UART chip and it's triggered interrupts
             **/
            struct InterruptIdentificationRegister {
                /**
                 * @brief The FIFO presence field tells the status of the FIFO if
                 * it is present or not and if it is functionning or not
                 **/
                uint8_t fifoPresence:2;
                /**
                 * @brief The Wide FIFO field indicates if the chip accepts a 64
                 * byte size FIFO. Use <i>FIFOControlRegister</i> if you want to
                 * alter it's value
                 **/
                bool wideFifo;
                /**
                 * @brief The Interrupt Status which indicates what is the last
                 * interrupt type called
                 **/
                uint8_t interruptStatus:3;
                /**
                 * @brief The Interrupt Pending Flags indicates if an interrupt
                 * is not yet assimilated to an interrupt
                 **/
                bool interruptPending;
            };

            /**
             * @brief The FIFO Control Register is the way to control how the
             * First In/First Out (FIFO) buffers will behave on the chip
             **/
            struct FIFOControlRegister {
                /**
                 * @brief The Interrupt Trigger Level field allows the triggering of
                 * a number of characters that would be stored in the FIFO before an
                 * interrupt occurs
                 **/
                uint8_t interruptLevel:2;
                /**
                 * @brief The Wide FIFO field indicates if the chip accepts a 64 byte
                 * size FIFO
                 **/
                bool wideFifo;
                /**
                 * @brief The Direct Memory Access Select field allows the retriving
                 * of data from the FIFO
                 **/
                bool dmaSelect;
                /**
                 * @brief The Clear Transmit FIFO field allows the FIFO internal
                 * buffer to be flushed out without sending it's content
                 **/
                bool clearTransmit;
                /**
                 * @brief The Clear Receive FIFO field allows the FIFO internal
                 * buffer to be cleared without reading it's content
                 **/
                bool clearReceive;
                /**
                 * @brief The Enable FIFO field allows the usage of the FIFO
                 * buffer. If the FIFO is disabled, awaiting data could be lost
                 **/
                bool enableFifo;
            };

            /**
             * @brief The Line Control Register allows the control of the data
             * sending pattern, and it's divisor latch
             **/
            struct LineControlRegister {
                /**
                 * @brief The divisor latch access field allows access to registers
                 * that are present only when it's value is positive, which permits
                 * the use of a total of 12 registers through 8 port addresses
                 **/
                bool latchAccess;
                /**
                 * @brief The break enable field allows the transfer to block it's
                 * input/output operations, until altered to negative
                 **/
                bool breakEnable;
                /**
                 * @brief The parity bits controls how the parity is handled
                 **/
                uint8_t parity:3;
                /**
                 * @brief The stop bits field controls how many bits are sent
                 * for each word
                 **/
                bool stopBits;
                /**
                 * @brief The word length controls how many data bits should be sent
                 * per word that is transmitted by the serial controller
                 **/
                uint8_t wordLength:2;
            };

            /**
             * @brief The Modem Control Register allows to control hardware
             * operations, under software control, which permits the direct
             * manipulation of four different outputs on the UART for example
             **/
            struct ModemControlRegister {
                /**
                 * @brief The autoflow control enabled field allows the
                 * UART to directly control the state of the RTS and the DTS
                 * for hardware character flow control, depending on the current state of the FIFO
                 **/
                bool autoflowEnabled;
                /**
                 * @brief The loopback field allows to test the UART to verify
                 * that the circuits are working between the processor and the UART
                 **/
                bool loopback;
                /**
                 * @brief The second auxiliary field which permits the enable
                 * of interrupts for example, which is needed by most of UARTs
                 **/
                bool secondAux;
                /**
                 * @brief The primary auxiliary which permits control of it. Take a
                 * look at the field <i>secondAux</i> for more details
                 **/
                bool primaryAux;
                /**
                 * @brief The send request field tells to the parallel device that
                 * data is waiting
                 **/
                bool sendRequest;
                /**
                 * @brief The data ready field tells to the parallel device that data
                 * has been received
                 **/
                bool dataReady;
            };

            /**
             * @brief The Line Status Register is used only to get information
             * on possible errors conditions that the UART could have thrown, based on
             * the data that has been received
             **/
            struct LineStatusRegister {
                /**
                 * @brief The FIFO error field indicates that the FIFO contains
                 * character errors, and needs to be cleaned
                 **/
                bool fifoError;
                /**
                 * @brief The Empty Data Holding Registers field allows the knowledge
                 * of correct data transfer
                 **/
                bool edRegisters;
                /**
                 * @brief The Empty Transmitter Holding Registers field allows the
                 * knowledge of correct shift register
                 **/
                bool ethRegister;
                /**
                 * @brief The Break Interrupt field tells if the serial data input
                 * got negative bits for an entire word
                 **/
                bool breakInterrupt;
                /**
                 * @brief The Framing Error field indicates if the last bit is not
                 * a stop bit; for example, a negative bit; or bad timing
                 **/
                bool framingError;
                /**
                 * @brief The Parity Error field tells if no parity pattern has been
                 * found; but can also be used to detect a baud rate mismatch
                 **/
                bool parityError;
                /**
                 * @brief The Overrun Error field indicates if the FIFO is full, or
                 * an character waiting to be read and the incoming shift register is
                 * attempting to move the contents of the next character into the
                 * receiver buffer
                 **/
                bool overrunError;
                /**
                 * @brief The Data Ready field indicates if data is available to
                 * be read from the UART
                 **/
                bool dataReady;
            };

            /**
             * @brief The Modem Status Register is present to inform to the status
             * of the modem. It's access in this manner can either be an external
             * or internal modem that uses a UART as it's interface for the computer
             **/
            struct ModemStatusRegister {
                /**
                 * @brief The Carrier Detect field indicates if the modem is connected
                 * to it's specified target
                 **/
                bool carrierDetect;
                /**
                 * @brief The Ring Indicator field tells if the modem is currently
                 * calling to it's specified target
                 **/
                bool ringIndicator;
                /**
                 * @brief The Data Set Ready field indicates if the data 
                 **/
                bool dsReady;
                /**
                 * @brief The Clear To Send field indicates if data will be sent over the
                 * target modem
                 **/
                bool ctSend;
                /**
                 * @brief The Delta Data Carrier Detect field indicates if the Carrier Detect
                 * field has changed during the communication
                 **/
                bool ddcDetect;
                /**
                 * @brief The Trailing Edge Ring Indicator field indicates if the Ring Indicator
                 * field has changed during the communication
                 **/
                bool terIndicator;
                /**
                 * @brief The Delta Data Set Ready field indicates if the Data Set Ready field
                 * has changed during the communication
                 **/
                bool ddsReady;
                /**
                 * @brief The Delta Clear To Send field indicates if the Clear To Send field has
                 * changed during the communication
                 **/
                bool dctSend;
            };

            /**
             * @brief The constructor of the object
             * @param address the address port to communicate
             * @param baudrate the speed of the communication
             * @param wLength the word length of the communication
             * @param parity the parity of the communication
             **/
            SerialPort(uint16_t address, uint32_t baudrate, uint8_t wLength, uint8_t parity);
            /**
             * @brief The constructor of the object
             * @param address the address port to communicate
             * @param baudrate the speed of the communication
             * @param wLength the word length of the communication
             **/
            SerialPort(uint16_t address, uint32_t baudrate, uint8_t wLength);
            /**
             * @brief The constructor of the object
             * @param address the address port to communicate
             * @param baudrate the speed of the communication
             **/
            SerialPort(uint16_t address, uint32_t baudrate);
            /**
             * @brief The constructor of the object
             * @param address the address port to communicate
             **/
            SerialPort(uint16_t address);

            /**
             * @brief Gets the Interrupt Enable Register
             * @param reg the Interrupt Enable Register structure pointer to fill in
             **/
            void getInterruptEnableRegister(OSMOS::IO::SerialPort::InterruptEnableRegister *reg);
            /**
             * @brief Sets the Interrupt Enable Register
             * @param reg the Interrupt Enable Register structure pointer to set
             **/
            void setInterruptEnableRegister(OSMOS::IO::SerialPort::InterruptEnableRegister *reg);

            /**
             * @brief Gets the Interrupt Identification Register
             * @param reg the Interrupt Identification Register structure pointer to fill in
             **/
            void getInterruptIdentificationRegister(OSMOS::IO::SerialPort::InterruptIdentificationRegister *reg);

            /**
             * @brief Sets the FIFO Control Register
             * @param reg the FIFO Control Register structure pointer to set
             **/
            void setFIFOControlRegister(OSMOS::IO::SerialPort::FIFOControlRegister *reg);

            /**
             * @brief Gets the Line Control Register
             * @param reg the Line Control Register structure pointer to fill in
             **/
            void getLineControlRegister(OSMOS::IO::SerialPort::LineControlRegister *reg);
            /**
             * @brief Sets the Line Control Register
             * @param reg the Line Control Register structure pointer to set
             **/
            void setLineControlRegister(OSMOS::IO::SerialPort::LineControlRegister *reg);

            /**
             * @brief Gets the Modem Control Register
             * @param reg the Modem Control Register structure pointer to fill in
             **/
            void getModemControlRegister(OSMOS::IO::SerialPort::ModemControlRegister *reg);
            /**
             * @brief Sets the Modem Control Register
             * @param reg the Modem Control Register structure pointer to set
             **/
            void setModemControlRegister(OSMOS::IO::SerialPort::ModemControlRegister *reg);

            /**
             * @brief Gets the Line Status Register
             * @param reg the Line Status Register structure pointer to fill in
             **/
            void getLineStatusRegister(OSMOS::IO::SerialPort::LineStatusRegister *reg);

            /**
             * @brief Gets the Modem Status Register
             * @param reg the Modem Status Register structure pointer to fill in
             **/
            void getModemStatusRegister(OSMOS::IO::SerialPort::ModemStatusRegister *reg);

            /**
             * @brief Sets the Divisor Latch Access Bit
             * @param access the access status to set
             **/
            void setDivisorLatchAccessBit(bool access);
            /**
             * @brief Gets the Divisor Latch Access Bit
             * @return the access status of the divisor
             **/
            bool getDivisorLatchAccessBit();

            /**
             * @brief Sets the baudrate/speed of communication, which should
             * have a dividende of the maximum baudrate/speed of communication,
             * which is 115200 bps
             * @param baudrate the baudrate/speed of communication
             **/
            void setBaudrate(uint32_t baudrate);
            /**
             * @brief Gets the baudrate/speed of communication in bits per
             * second (bps)
             * @return the baudrate/speed of communication in bits per second
             * (bps)
             **/
            uint32_t getBaudrate();

            /**
             * @brief Checks if data has been sent from the target serial port
             * @return the awaiting status of data
             **/
            bool isDataAwaiting();

            /**
             * @brief Receives a byte-sized value from the specified
             * serial port
             * @param value the value pointer to assign
             **/
            void in(uint8_t *value);
            /**
             * @brief Receives a word-sized value from the specified
             * serial port
             * @param value the value pointer to assign
             **/
            void in(uint16_t *value);
            /**
             * @brief Receives a double word-sized value from the
             * specified serial port
             * @param value the value pointer to assign
             **/
            void in(uint32_t *value);
            /**
             * @brief Receives a string terminating with a NULL character
             * from the specified serial port
             * @param str the string to read
             **/
            void in(char *str);
            
            /**
             * @brief Sends a byte-sized value from the specified
             * serial port
             * @param value the value to send
             **/
            void out(uint8_t value);
            /**
             * @brief Sends a word-sized value from the specified
             * serial port
             * @param value the value to send
             **/
            void out(uint16_t value);
            /**
             * @brief Sends a double word-sized value from the
             * specified serial port
             * @param value the value to send
             **/
            void out(uint32_t value);
            /**
             * @brief Sends a string from the specified serial port
             * @param str the string to send
             **/
            void out(const char *str);
        };
    };
};