/**
 * @file core-minimal/osmos/io/serial.cpp
 * @brief The main code for the SerialPort class
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

#include "serial.hpp"

#include "port.hpp"

const uint16_t OSMOS::IO::SerialPort::COMMUNICATION_PORT_1                       = 0x3F8;
const uint16_t OSMOS::IO::SerialPort::COMMUNICATION_PORT_2                       = 0x2F8;
const uint16_t OSMOS::IO::SerialPort::COMMUNICATION_PORT_3                       = 0x3E8;
const uint16_t OSMOS::IO::SerialPort::COMMUNICATION_PORT_4                       = 0x2E8;

const uint8_t OSMOS::IO::SerialPort::FIFO_NOT_AVAILABLE                          = 0b00;
const uint8_t OSMOS::IO::SerialPort::FIFO_RESERVED_CONDITION                     = 0b01;
const uint8_t OSMOS::IO::SerialPort::FIFO_ENABLED_OFF                            = 0b10;
const uint8_t OSMOS::IO::SerialPort::FIFO_ENABLED                                = 0b11;

const uint8_t OSMOS::IO::SerialPort::IIRSTATUS_MODEM_STATUS_INTERRUPT            = 0b000;
const uint8_t OSMOS::IO::SerialPort::IIRSTATUS_EMPTY_THR_INTERRUPT               = 0b001;
const uint8_t OSMOS::IO::SerialPort::IIRSTATUS_RECEIVED_DATA_AVAILABLE_INTERRUPT = 0b010;
const uint8_t OSMOS::IO::SerialPort::IIRSTATUS_RECEIVER_LINE_STATUS_INTERRUPT    = 0b011;
const uint8_t OSMOS::IO::SerialPort::IIRSTATUS_TIMEOUT_INTERRUPT_PENDING         = 0b110;

const uint8_t OSMOS::IO::SerialPort::LCR_WORDLENGTH_5BITS                        = 0b00;
const uint8_t OSMOS::IO::SerialPort::LCR_WORDLENGTH_6BITS                        = 0b01;
const uint8_t OSMOS::IO::SerialPort::LCR_WORDLENGTH_7BITS                        = 0b10;
const uint8_t OSMOS::IO::SerialPort::LCR_WORDLENGTH_8BITS                        = 0b11;

const uint8_t OSMOS::IO::SerialPort::LCR_PARITY_NONE                             = 0b000;
const uint8_t OSMOS::IO::SerialPort::LCR_PARITY_ODD                              = 0b001;
const uint8_t OSMOS::IO::SerialPort::LCR_PARITY_EVEN                             = 0b011;
const uint8_t OSMOS::IO::SerialPort::LCR_PARITY_MARK                             = 0b101;
const uint8_t OSMOS::IO::SerialPort::LCR_PARITY_SPACE                            = 0b111;

const bool OSMOS::IO::SerialPort::ONE_STOP_BIT                                   = false;
const bool OSMOS::IO::SerialPort::ONE_HALF_STOP_BIT                              = true;

void OSMOS::IO::SerialPort::setup(uint16_t address, uint32_t baudrate, uint8_t wLength, uint8_t parity) {
    switch (address) {
        default:
            __attribute__((fallthrough));
        case OSMOS::IO::SerialPort::COMMUNICATION_PORT_1:
            this->portAddress = OSMOS::IO::SerialPort::COMMUNICATION_PORT_1;
            break;
        case OSMOS::IO::SerialPort::COMMUNICATION_PORT_2:
            this->portAddress = OSMOS::IO::SerialPort::COMMUNICATION_PORT_2;
            break;
        case OSMOS::IO::SerialPort::COMMUNICATION_PORT_3:
            this->portAddress = OSMOS::IO::SerialPort::COMMUNICATION_PORT_3;
            break;
        case OSMOS::IO::SerialPort::COMMUNICATION_PORT_4:
            this->portAddress = OSMOS::IO::SerialPort::COMMUNICATION_PORT_4;
            break;
    }

    this->port = new OSMOS::IO::Port(this->portAddress);
    
    OSMOS::IO::SerialPort::InterruptEnableRegister *intReg = new OSMOS::IO::SerialPort::InterruptEnableRegister;
    intReg->lowPowerMode = false;
    intReg->msInterrupt = false;
    intReg->rdaInterrupt = false;
    intReg->rsInterrupt = false;
    intReg->sleepMode = false;
    intReg->threiInterrupt = false;
    OSMOS::IO::SerialPort::setInterruptEnableRegister(intReg);

    OSMOS::IO::SerialPort::LineControlRegister *lcrReg = new OSMOS::IO::SerialPort::LineControlRegister;
    OSMOS::IO::SerialPort::setBaudrate(baudrate);

    OSMOS::IO::SerialPort::getLineControlRegister(lcrReg);
    lcrReg->parity = parity;
    lcrReg->wordLength = wLength;
    lcrReg->stopBits = OSMOS::IO::SerialPort::ONE_STOP_BIT;
    OSMOS::IO::SerialPort::setLineControlRegister(lcrReg);

    OSMOS::IO::SerialPort::FIFOControlRegister *fifoReg = new OSMOS::IO::SerialPort::FIFOControlRegister;
    fifoReg->enableFifo = true;
    fifoReg->clearReceive = true;
    fifoReg->clearTransmit = true;
    fifoReg->interruptLevel = 0;
    fifoReg->dmaSelect = false;
    OSMOS::IO::SerialPort::setFIFOControlRegister(fifoReg);

    OSMOS::IO::SerialPort::ModemControlRegister *modReg = new OSMOS::IO::SerialPort::ModemControlRegister;
    modReg->dataReady = false;
    modReg->sendRequest = true;
    modReg->autoflowEnabled = true;
    OSMOS::IO::SerialPort::setModemControlRegister(modReg);
}

OSMOS::IO::SerialPort::SerialPort(uint16_t address, uint32_t baudrate, uint8_t wLength, uint8_t parity) {
    OSMOS::IO::SerialPort::setup(address, baudrate, wLength, parity);
}

OSMOS::IO::SerialPort::SerialPort(uint16_t address, uint32_t baudrate, uint8_t wLength) {
    OSMOS::IO::SerialPort::setup(address, baudrate, wLength, OSMOS::IO::SerialPort::LCR_PARITY_NONE);
}

OSMOS::IO::SerialPort::SerialPort(uint16_t address, uint32_t baudrate) {
    OSMOS::IO::SerialPort::setup(address, baudrate, OSMOS::IO::SerialPort::LCR_WORDLENGTH_8BITS, OSMOS::IO::SerialPort::LCR_PARITY_NONE);
}

OSMOS::IO::SerialPort::SerialPort(uint16_t address) {
    OSMOS::IO::SerialPort::setup(address, 115200 / 3, OSMOS::IO::SerialPort::LCR_WORDLENGTH_8BITS, OSMOS::IO::SerialPort::LCR_PARITY_NONE);
}

void OSMOS::IO::SerialPort::getInterruptEnableRegister(OSMOS::IO::SerialPort::InterruptEnableRegister *reg) {
    if (OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
    uint8_t ier = NULL;
    OSMOS::IO::Port::in(this->portAddress + 1, &ier);

    reg->lowPowerMode       = (ier & 0b00100000 ? true : false);
    reg->sleepMode          = (ier & 0b00010000 ? true : false);
    reg->msInterrupt        = (ier & 0b00001000 ? true : false);
    reg->rsInterrupt        = (ier & 0b00000100 ? true : false);
    reg->threiInterrupt     = (ier & 0b00000010 ? true : false);
    reg->rdaInterrupt       = (ier & 0b00000001 ? true : false);
}

void OSMOS::IO::SerialPort::setInterruptEnableRegister(OSMOS::IO::SerialPort::InterruptEnableRegister *reg) {
    if (OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
    uint8_t ier = NULL;
    ier = (reg->lowPowerMode ? 0b1 : 0b0) << 5   |
          (reg->sleepMode ? 0b1 : 0b0) << 4      |
          (reg->msInterrupt ? 0b1 : 0b0) << 3    |
          (reg->rsInterrupt ? 0b1 : 0b0) << 2    |
          (reg->threiInterrupt ? 0b1 : 0b0) << 1 |
          reg->rdaInterrupt ? 0b1 : 0b0;

    OSMOS::IO::Port::out(this->portAddress + 1, ier);
}

void OSMOS::IO::SerialPort::getInterruptIdentificationRegister(OSMOS::IO::SerialPort::InterruptIdentificationRegister *reg) {
    uint8_t iir = NULL;
    OSMOS::IO::Port::in(this->portAddress + 2, &iir);

    reg->fifoPresence       = ((iir & 0b11000000) >> 6) & 0b11;
    reg->wideFifo           = (iir & 0b00100000 ? true : false);
    reg->interruptStatus    = (iir & 0b00001110 >> 1) & 0b111;
    reg->interruptPending   = (iir & 0b00000001 ? true : false);
}

void OSMOS::IO::SerialPort::setFIFOControlRegister(OSMOS::IO::SerialPort::FIFOControlRegister *reg) {
    uint8_t fcr = NULL;
    fcr = (reg->interruptLevel & 0b11) << 6     |
          (reg->wideFifo ? 0b1 : 0b0) << 5      |
          (reg->dmaSelect ? 0b1 : 0b0) << 3     |
          (reg->clearTransmit ? 0b1 : 0b0) << 2 |
          (reg->clearReceive ? 0b1 : 0b0) << 1  |
          (reg->enableFifo ? 0b1 : 0b0);

    OSMOS::IO::Port::out(this->portAddress + 2, fcr);
}

void OSMOS::IO::SerialPort::getLineControlRegister(OSMOS::IO::SerialPort::LineControlRegister *reg) {
    uint8_t lcr = NULL;
    OSMOS::IO::Port::in(this->portAddress + 3, &lcr);

    reg->latchAccess = (lcr & 0b10000000 ? true : false);
    reg->breakEnable = (lcr & 0b01000000 ? true : false);
    reg->parity      = ((lcr & 0b00111000) >> 3);
    reg->stopBits    = (lcr & 0b00000100 ? true : false);
    reg->wordLength  = (lcr & 0b00000011);
}

void OSMOS::IO::SerialPort::setLineControlRegister(OSMOS::IO::SerialPort::LineControlRegister *reg) {
    uint8_t lcr = NULL;
    lcr = (reg->latchAccess ? 0b1 : 0b0) << 7   |
          (reg->breakEnable ? 0b1 : 0b0) << 6   |
          (reg->parity & 0b111) << 3            |
          (reg->stopBits ? 0b1 : 0b0) << 2      |
          (reg->wordLength & 0b11);

    OSMOS::IO::Port::out(this->portAddress + 3, lcr);
}

void OSMOS::IO::SerialPort::getModemControlRegister(OSMOS::IO::SerialPort::ModemControlRegister *reg) {
    uint8_t mcr = NULL;
    OSMOS::IO::Port::in(this->portAddress + 4, &mcr);

    reg->autoflowEnabled = (mcr & 0b00100000 ? true : false);
    reg->loopback        = (mcr & 0b00010000 ? true : false);
    reg->secondAux       = (mcr & 0b00001000 ? true : false);
    reg->primaryAux      = (mcr & 0b00000100 ? true : false);
    reg->sendRequest     = (mcr & 0b00000010 ? true : false);
    reg->dataReady       = (mcr & 0b00000001 ? true : false);
}

void OSMOS::IO::SerialPort::setModemControlRegister(OSMOS::IO::SerialPort::ModemControlRegister *reg) {
    uint8_t mcr = NULL;
    mcr = (reg->autoflowEnabled ? 0b1 : 0b0) << 5 |
          (reg->loopback ? 0b1 : 0b0) << 4        |
          (reg->secondAux ? 0b1 : 0b0) << 3       |
          (reg->primaryAux ? 0b1 : 0b0) << 2      |
          (reg->sendRequest ? 0b1 : 0b0) << 1     |
          reg->dataReady ? 0b1 : 0b0;

    OSMOS::IO::Port::out(this->portAddress + 4, mcr);
}

void OSMOS::IO::SerialPort::getLineStatusRegister(OSMOS::IO::SerialPort::LineStatusRegister *reg) {
    uint8_t lsr = NULL;
    OSMOS::IO::Port::in(this->portAddress + 5, &lsr);

    reg->fifoError = (lsr & 0b10000000 ? true : false);
    reg->edRegisters = (lsr & 0b01000000 ? true : false);
    reg->ethRegister = (lsr & 0b00100000 ? true : false);
    reg->breakInterrupt = (lsr & 0b00010000 ? true : false);
    reg->framingError = (lsr & 0b00001000 ? true : false);
    reg->parityError = (lsr & 0b00000100 ? true : false);
    reg->overrunError = (lsr & 0b00000010 ? true : false);
    reg->dataReady = (lsr & 0b00000001 ? true : false);
}

void OSMOS::IO::SerialPort::getModemStatusRegister(OSMOS::IO::SerialPort::ModemStatusRegister *reg) {
    uint8_t msr = NULL;
    OSMOS::IO::Port::in(this->portAddress + 6, &msr);

    reg->carrierDetect = (msr & 0b10000000 ? true : false);
    reg->ringIndicator = (msr & 0b01000000 ? true : false);
    reg->dsReady = (msr & 0b00100000 ? true : false);
    reg->ctSend = (msr & 0b00010000 ? true : false);
    reg->ddcDetect = (msr & 0b00001000 ? true : false);
    reg->terIndicator = (msr & 0b00000100 ? true : false);
    reg->ddsReady = (msr & 0b00000010 ? true : false);
    reg->dctSend = (msr & 0b00000001 ? true : false);
}

void OSMOS::IO::SerialPort::setDivisorLatchAccessBit(bool access) {
    OSMOS::IO::SerialPort::LineControlRegister *reg = new OSMOS::IO::SerialPort::LineControlRegister;
    OSMOS::IO::SerialPort::getLineControlRegister(reg);

    reg->latchAccess = access;
    OSMOS::IO::SerialPort::setLineControlRegister(reg);
}

bool OSMOS::IO::SerialPort::getDivisorLatchAccessBit() {
    OSMOS::IO::SerialPort::LineControlRegister *reg = new OSMOS::IO::SerialPort::LineControlRegister;
    OSMOS::IO::SerialPort::getLineControlRegister(reg);

    return reg->latchAccess;
}

void OSMOS::IO::SerialPort::setBaudrate(uint32_t baudrate) {
    OSMOS::IO::SerialPort::setDivisorLatchAccessBit(true);

    uint32_t div = 115200 / baudrate;
    OSMOS::IO::Port::out(this->portAddress + 1, (div >> 8) & 0xFF);
    OSMOS::IO::Port::out(this->portAddress, div & 0xFF);

    OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
}

uint32_t OSMOS::IO::SerialPort::getBaudrate() {
    if (!OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(true);

    uint16_t hi, lo;
    OSMOS::IO::Port::in(this->portAddress + 1, &hi);
    OSMOS::IO::Port::in(this->portAddress, &lo);

    uint32_t div = hi << 8 | lo;
    return div * 115200;
}

bool OSMOS::IO::SerialPort::isDataAwaiting() {
    OSMOS::IO::SerialPort::LineStatusRegister *lsr = new OSMOS::IO::SerialPort::LineStatusRegister;
    OSMOS::IO::SerialPort::getLineStatusRegister(lsr);

    return lsr->dataReady;
}

void OSMOS::IO::SerialPort::in(uint8_t *value) {
    if (OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
    this->port->in(value);
}

void OSMOS::IO::SerialPort::in(uint16_t *value) {
    if (OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
    this->port->in(value);
}

void OSMOS::IO::SerialPort::in(uint32_t *value) {
    if (OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
    this->port->in(value);
}

void OSMOS::IO::SerialPort::in(char *str) {
    if (OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
    this->port->in(str);
}

void OSMOS::IO::SerialPort::out(uint8_t value) {
    if (OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
    this->port->out(value);
}

void OSMOS::IO::SerialPort::out(uint16_t value) {
    if (OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
    this->port->out(value);
}

void OSMOS::IO::SerialPort::out(uint32_t value) {
    if (OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
    this->port->out(value);
}

void OSMOS::IO::SerialPort::out(const char *str) {
    if (OSMOS::IO::SerialPort::getDivisorLatchAccessBit())
        OSMOS::IO::SerialPort::setDivisorLatchAccessBit(false);
    this->port->out(str);
}