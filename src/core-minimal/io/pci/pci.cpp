/*
 * The PCI controller, in order to handle peripherals such as IDE disks.
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

#include "pci.hpp"
#include "../io.hpp"

#include "../vga_display.hpp"

const uint_8 IO::PCI::Class::Basic::CLASS_CODE 							= 0x00;
const uint_8 IO::PCI::Class::Basic::NON_VGA_DISPLAY_DEVICE 				= 0x00;
const uint_8 IO::PCI::Class::Basic::VGA_DISPLAY_DEVICE 					= 0x01;

const uint_8 IO::PCI::Class::Storage::CLASS_CODE 						= 0x01;
const uint_8 IO::PCI::Class::Storage::SCSI_BUS_CONTROLLER				= 0x00;
const uint_8 IO::PCI::Class::Storage::IDE_CONTROLLER					= 0x01;
const uint_8 IO::PCI::Class::Storage::FLOPPY_DISK_CONTROLLER			= 0x02;
const uint_8 IO::PCI::Class::Storage::IPI_BUS_CONTROLLER				= 0x03;
const uint_8 IO::PCI::Class::Storage::RAID_CONTROLLER					= 0x04;
const uint_8 IO::PCI::Class::Storage::ATA_CONTROLLER					= 0x05;
const uint_8 IO::PCI::Class::Storage::SERIAL_ATA_CONTROLLER				= 0x06;
const uint_8 IO::PCI::Class::Storage::SERIAL_ATTACHED_SCSI_CONTROLLER	= 0x07;
const uint_8 IO::PCI::Class::Storage::OTHER_STORAGE_CONTROLLER			= 0x80;

const uint_8 IO::PCI::Class::Network::CLASS_CODE						= 0x02;
const uint_8 IO::PCI::Class::Network::ETHERNET_CONTROLLER				= 0x00;
const uint_8 IO::PCI::Class::Network::TOKEN_RING_CONTROLLER				= 0x01;
const uint_8 IO::PCI::Class::Network::FDDI_CONTROLLER					= 0x02;
const uint_8 IO::PCI::Class::Network::ATM_CONTROLLER					= 0x03;
const uint_8 IO::PCI::Class::Network::ISDN_CONTROLLER					= 0x04;
const uint_8 IO::PCI::Class::Network::WORLDFIP_CONTROLLER				= 0x05;
const uint_8 IO::PCI::Class::Network::PICMG_MULTI_COMPUTING_CONTROLLER	= 0x06;
const uint_8 IO::PCI::Class::Network::OTHER_NETWORK_CONTROLLER			= 0x80;

const uint_8 IO::PCI::Class::Display::CLASS_CODE						= 0x03;
const uint_8 IO::PCI::Class::Display::DISPLAY_CONTROLLER				= 0x00;
const uint_8 IO::PCI::Class::Display::DXGA_CONTROLLER					= 0x01;
const uint_8 IO::PCI::Class::Display::D3D_CONTROLLER					= 0x02;
const uint_8 IO::PCI::Class::Display::OTHER_DISPLAY_CONTROLLER			= 0x80;

const uint_8 IO::PCI::Class::Multimedia::CLASS_CODE						= 0x04;
const uint_8 IO::PCI::Class::Multimedia::VIDEO_DEVICE					= 0x00;
const uint_8 IO::PCI::Class::Multimedia::AUDIO_DEVICE					= 0x01;
const uint_8 IO::PCI::Class::Multimedia::COMPUTER_TELEPHONY_DEVICE		= 0x02;
const uint_8 IO::PCI::Class::Multimedia::OTHER_MULTIMEDIA_DEVICE		= 0x80;

const uint_8 IO::PCI::Class::Memory::CLASS_CODE							= 0x05;
const uint_8 IO::PCI::Class::Memory::RAM_CONTROLLER						= 0x00;
const uint_8 IO::PCI::Class::Memory::FLASH_CONTROLLER					= 0x01;
const uint_8 IO::PCI::Class::Memory::OTHER_MEMORY_CONTROLLER			= 0x80;

const uint_8 IO::PCI::Class::Bridge::CLASS_CODE							= 0x06;
const uint_8 IO::PCI::Class::Bridge::HOST_BRIDGE						= 0x00;
const uint_8 IO::PCI::Class::Bridge::ISA_BRIDGE							= 0x01;
const uint_8 IO::PCI::Class::Bridge::EISA_BRIDGE						= 0x02;
const uint_8 IO::PCI::Class::Bridge::MCA_BRIDGE							= 0x03;
const uint_8 IO::PCI::Class::Bridge::PCI_BRIDGE							= 0x04;
const uint_8 IO::PCI::Class::Bridge::PCMCIA_BRIDGE						= 0x05;
const uint_8 IO::PCI::Class::Bridge::NUBUS_BRIDGE						= 0x06;
const uint_8 IO::PCI::Class::Bridge::CARDBUS_BRIDGE						= 0x07;
const uint_8 IO::PCI::Class::Bridge::RACEWAY_BRIDGE						= 0x08;
const uint_8 IO::PCI::Class::Bridge::PCI_BRIDGE_SEMI_TRANSPARENT		= 0x09;
const uint_8 IO::PCI::Class::Bridge::INFINIBRAND_BRIDGE					= 0x0A;
const uint_8 IO::PCI::Class::Bridge::OTHER_BRIDGE_DEVICE				= 0x80;

const uint_8 IO::PCI::Class::Communication::CLASS_CODE					= 0x07;
const uint_8 IO::PCI::Class::Communication::XT_SERIAL_CONTROLLER		= 0x00;
const uint_8 IO::PCI::Class::Communication::PARALLEL_PORT				= 0x01;
const uint_8 IO::PCI::Class::Communication::MULTIPORT_SERIAL_CONTROLLER	= 0x02;
const uint_8 IO::PCI::Class::Communication::GENERIC_MODEM				= 0x03;
const uint_8 IO::PCI::Class::Communication::IEEE_CONTROLLER				= 0x04;
const uint_8 IO::PCI::Class::Communication::SMART_CARD					= 0x05;
const uint_8 IO::PCI::Class::Communication::OTHER_COMMUNICATION_DEVICE	= 0x80;

const uint_8 IO::PCI::Class::Peripheral::System::CLASS_CODE				= 0x08;
const uint_8 IO::PCI::Class::Peripheral::System::PIC					= 0x00;
const uint_8 IO::PCI::Class::Peripheral::System::DMA_CONTROLLER			= 0x01;
const uint_8 IO::PCI::Class::Peripheral::System::SYSTEM_TIMER			= 0x02;
const uint_8 IO::PCI::Class::Peripheral::System::RTC_CONTROLLER			= 0x03;
const uint_8 IO::PCI::Class::Peripheral::System::PCI_HOTPLUG_CONTROLLER	= 0x04;
const uint_8 IO::PCI::Class::Peripheral::System::OTHER_SYSTEM_PERIPHERAL= 0x80;

const uint_8 IO::PCI::Class::Peripheral::User::CLASS_CODE				= 0x09;
const uint_8 IO::PCI::Class::Peripheral::User::KEYBOARD_CONTROLLER		= 0x00;
const uint_8 IO::PCI::Class::Peripheral::User::DIGITIZER				= 0x01;
const uint_8 IO::PCI::Class::Peripheral::User::MOUSE_CONTROLLER			= 0x02;
const uint_8 IO::PCI::Class::Peripheral::User::SCANNER_CONTROLLER		= 0x03;
const uint_8 IO::PCI::Class::Peripheral::User::GAMEPORT_CONTROLLER		= 0x04;
const uint_8 IO::PCI::Class::Peripheral::User::OTHER_INPUT_CONTROLLER	= 0x80;

const uint_8 IO::PCI::Class::Docker::CLASS_CODE							= 0x0A;
const uint_8 IO::PCI::Class::Docker::GENERIC_DOCKING_STATION			= 0x00;
const uint_8 IO::PCI::Class::Docker::OTHER_DOCKING_STATION				= 0x80;

const uint_8 IO::PCI::Class::Processor::CLASS_CODE						= 0x0B;
const uint_8 IO::PCI::Class::Processor::I386_PROCESSOR					= 0x00;
const uint_8 IO::PCI::Class::Processor::I486_PROCESSOR					= 0x01;
const uint_8 IO::PCI::Class::Processor::PENTIUM_PROCESSOR				= 0x02;
const uint_8 IO::PCI::Class::Processor::ALPHA_PROCESSOR					= 0x10;
const uint_8 IO::PCI::Class::Processor::POWERPC_PROCESSOR				= 0x20;
const uint_8 IO::PCI::Class::Processor::MIPS_PROCESSOR					= 0x30;
const uint_8 IO::PCI::Class::Processor::CO_PROCESSOR					= 0x40;

const uint_8 IO::PCI::Class::SerialBus::CLASS_CODE						= 0x0C;
const uint_8 IO::PCI::Class::SerialBus::IEEE_1394_BUS					= 0x00;
const uint_8 IO::PCI::Class::SerialBus::ACCESS_BUS						= 0x01;
const uint_8 IO::PCI::Class::SerialBus::SSA_BUS							= 0x02;
const uint_8 IO::PCI::Class::SerialBus::USB_BUS							= 0x03;
const uint_8 IO::PCI::Class::SerialBus::FIBRE_CHANNEL_BUS				= 0x04;
const uint_8 IO::PCI::Class::SerialBus::SM_BUS							= 0x05;
const uint_8 IO::PCI::Class::SerialBus::INFINIBAND_BUS					= 0x06;
const uint_8 IO::PCI::Class::SerialBus::IPMI_SMIC_BUS					= 0x07;
const uint_8 IO::PCI::Class::SerialBus::SERCOS_BUS						= 0x08;
const uint_8 IO::PCI::Class::SerialBus::CAN_BUS							= 0x09;

const uint_8 IO::PCI::Class::Wireless::CLASS_CODE						= 0x0D;
const uint_8 IO::PCI::Class::Wireless::IRDA_CONTROLLER					= 0x00;
const uint_8 IO::PCI::Class::Wireless::CONSUMER_IR_CONTROLLER			= 0x01;
const uint_8 IO::PCI::Class::Wireless::RF_CONTROLLER					= 0x10;
const uint_8 IO::PCI::Class::Wireless::BLUETOOTH_CONTROLLER				= 0x11;
const uint_8 IO::PCI::Class::Wireless::BROADBAND_CONTROLLER				= 0x12;
const uint_8 IO::PCI::Class::Wireless::ETHERNET_CONTROLLER_A			= 0x20;
const uint_8 IO::PCI::Class::Wireless::ETHERNET_CONTROLLER_B			= 0x21;
const uint_8 IO::PCI::Class::Wireless::OTHER_WIRELESS_CONTROLLER		= 0x80;

const uint_8 IO::PCI::Class::IntelligentIO::CLASS_CODE					= 0x0E;
const uint_8 IO::PCI::Class::IntelligentIO::FIFO_MESSAGE				= 0x00;
const uint_8 IO::PCI::Class::IntelligentIO::I20_ARCHITECTURE			= 0x01;

const uint_8 IO::PCI::Class::Satellite::CLASS_CODE						= 0x0F;
const uint_8 IO::PCI::Class::Satellite::TV_CONTROLLER					= 0x01;
const uint_8 IO::PCI::Class::Satellite::AUDIO_CONTROLLER				= 0x02;
const uint_8 IO::PCI::Class::Satellite::VOICE_CONTROLLER				= 0x03;
const uint_8 IO::PCI::Class::Satellite::DATA_CONTROLLER					= 0x04;

const uint_8 IO::PCI::Class::Cryptography::CLASS_CODE								= 0x10;
const uint_8 IO::PCI::Class::Cryptography::NETWORK_CRYPTOGRAPHY_CONTROLLER			= 0x00;
const uint_8 IO::PCI::Class::Cryptography::ENTERTAINMENT_CRYPTOGRAPHY_CONTROLLER	= 0x10;
const uint_8 IO::PCI::Class::Cryptography::OTHER_CRYPTOGRAPHY_CONTROLLER			= 0x80;

const uint_8 IO::PCI::Class::Acquisition::CLASS_CODE					= 0x11;
const uint_8 IO::PCI::Class::Acquisition::DPIO_MODULE					= 0x00;
const uint_8 IO::PCI::Class::Acquisition::PERFORMANCE_COUNTER			= 0x01;
const uint_8 IO::PCI::Class::Acquisition::CSPT_METER					= 0x10;
const uint_8 IO::PCI::Class::Acquisition::MANAGEMENT_CARD				= 0x20;
const uint_8 IO::PCI::Class::Acquisition::OTHER_ACQUISITION_CONTROLLER	= 0x80;

IO::Port *IO::PCI::CAM::command_port = new IO::Port(0x0CF8);
IO::Port *IO::PCI::CAM::data_port = new IO::Port(0x0CFC);

void IO::PCI::CAM::select(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg) {
	uint_32 sel = 0x1 << 31 | ((bus & 0xFF) << 16) | ((slot & 0x1F) << 11) | ((function & 0x7) << 8) | ((reg & 0xFC));
	IO::PCI::CAM::command_port->out(sel);
	//IO::Port::out(sel, 0xCF8);
}

void IO::PCI::CAM::read(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_32 *val) {
	IO::PCI::CAM::select(bus, slot, function, reg);
	uint_32 wval;
	IO::PCI::CAM::data_port->in(&wval);
	//IO::Port::in(0xCFC, &wval);
	*val = wval >> (8 * (reg % 4));
}

void IO::PCI::CAM::read(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_16 *val) {
	uint_32 wval;
	IO::PCI::CAM::read(bus, slot, function, reg, &wval);
	*val = wval & 0xFFFF;
}
void IO::PCI::CAM::read(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_8 *val) {
	uint_32 wval;
	IO::PCI::CAM::read(bus, slot, function, reg, &wval);
	*val = wval & 0xFF;
}

void IO::PCI::CAM::write(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_32 val) {
	IO::PCI::CAM::select(bus, slot, function, reg);
	IO::PCI::CAM::data_port->out(val);
	//IO::Port::out(val, 0xCFC);
}

void IO::PCI::CAM::write(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_16 val) {
	IO::PCI::CAM::write(bus, slot, function, reg, val);
}

void IO::PCI::CAM::write(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_8 val) {
	IO::PCI::CAM::write(bus, slot, function, reg, val);
}

void IO::PCI::CAM::getType(uint_8 bus, uint_8 slot, uint_8 function, uint_8 *type) {
	IO::PCI::CAM::read(bus, slot, function, 0x0D, type);
}

void IO::PCI::CAM::getVendor(uint_8 bus, uint_8 slot, uint_8 function, uint_16 *vendor) {
	IO::PCI::CAM::read(bus, slot, function, 0x02, vendor);
}

bool IO::PCI::CAM::isValid(uint_8 bus, uint_8 slot, uint_8 function) {
	uint_16 vq = 0x0000;
	IO::PCI::CAM::getVendor(bus, slot, function, &vq);

	return (vq != 0xFFFF && vq != 0x0000);
}

void IO::PCI::CAM::getBasicDevice(uint_8 bus, uint_8 slot, uint_8 function, struct IO::PCI::CAM::BasicDevice *device) {
	if (!IO::PCI::CAM::isValid(bus, slot, function))
		return;

	device->bus = bus;
	device->slot = slot;
	device->function = function;

	IO::PCI::CAM::read(bus, slot, function, 0x00, &device->device_id);
	IO::PCI::CAM::read(bus, slot, function, 0x02, &device->vendor_id);
	IO::PCI::CAM::read(bus, slot, function, 0x04, &device->status);
	IO::PCI::CAM::read(bus, slot, function, 0x06, &device->command);
	IO::PCI::CAM::read(bus, slot, function, 0x08, &device->class_code);
	IO::PCI::CAM::read(bus, slot, function, 0x09, &device->subclass);
	IO::PCI::CAM::read(bus, slot, function, 0x0A, &device->prog_if);
	IO::PCI::CAM::read(bus, slot, function, 0x0B, &device->revision_id);
	IO::PCI::CAM::read(bus, slot, function, 0x0C, &device->bist);
	IO::PCI::CAM::read(bus, slot, function, 0x0D, &device->header_type);
	IO::PCI::CAM::read(bus, slot, function, 0x0E, &device->latency_timer);
	IO::PCI::CAM::read(bus, slot, function, 0x0F, &device->cache_line_size);
}

void IO::PCI::CAM::getCommonDevice(uint_8 bus, uint_8 slot, uint_8 function, struct IO::PCI::CAM::CommonDevice *device) {
	if (!IO::PCI::CAM::isValid(bus, slot, function))
		return;

	uint_8 type = 0x00;
	IO::PCI::CAM::getType(bus, slot, function, &type);
	if (type != 0x00)
		return;

	IO::PCI::CAM::getBasicDevice(bus, slot, function, device);

	if (device->header_type == 0x00) {
		IO::PCI::CAM::read(bus, slot, function, 0x10, &device->bar0);
		IO::PCI::CAM::read(bus, slot, function, 0x14, &device->bar1);
		IO::PCI::CAM::read(bus, slot, function, 0x18, &device->bar2);
		IO::PCI::CAM::read(bus, slot, function, 0x1C, &device->bar3);
		IO::PCI::CAM::read(bus, slot, function, 0x20, &device->bar4);
		IO::PCI::CAM::read(bus, slot, function, 0x24, &device->bar5);

		IO::PCI::CAM::read(bus, slot, function, 0x28, &device->cis_pointer);
		IO::PCI::CAM::read(bus, slot, function, 0x2C, &device->subsystem_id);
		IO::PCI::CAM::read(bus, slot, function, 0x2E, &device->subsystem_vendor);
		IO::PCI::CAM::read(bus, slot, function, 0x30, &device->expansion_address);
		IO::PCI::CAM::read(bus, slot, function, 0x37, &device->capabilities_pointer);
		IO::PCI::CAM::read(bus, slot, function, 0x3C, &device->max_latency);
		IO::PCI::CAM::read(bus, slot, function, 0x3D, &device->min_grant);
		IO::PCI::CAM::read(bus, slot, function, 0x3E, &device->interrupt_pin);
		IO::PCI::CAM::read(bus, slot, function, 0x3F, &device->interrupt_line);	
	}
}

void IO::PCI::CAM::getBridgeDevice(uint_8 bus, uint_8 slot, uint_8 function, struct IO::PCI::CAM::BridgeDevice *device) {
	if (!IO::PCI::CAM::isValid(bus, slot, function))
		return;

	uint_8 type = 0x00;
	IO::PCI::CAM::getType(bus, slot, function, &type);
	if (type != 0x01)
		return;

	IO::PCI::CAM::getBasicDevice(bus, slot, function, device);

	if (device->header_type == 0x01) {
		IO::PCI::CAM::read(bus, slot, function, 0x10, &device->bar0);
		IO::PCI::CAM::read(bus, slot, function, 0x14, &device->bar1);
		IO::PCI::CAM::read(bus, slot, function, 0x18, &device->secondary_latency_timer);
		IO::PCI::CAM::read(bus, slot, function, 0x19, &device->subordinate_bus_number);
		IO::PCI::CAM::read(bus, slot, function, 0x1A, &device->secondary_bus_number);
		IO::PCI::CAM::read(bus, slot, function, 0x1B, &device->primary_bus_number);
		IO::PCI::CAM::read(bus, slot, function, 0x1C, &device->secondary_status);
		IO::PCI::CAM::read(bus, slot, function, 0x1E, &device->io_limit);
		IO::PCI::CAM::read(bus, slot, function, 0x1F, &device->io_base);
		IO::PCI::CAM::read(bus, slot, function, 0x20, &device->memory_limit);
		IO::PCI::CAM::read(bus, slot, function, 0x22, &device->memory_base);
		IO::PCI::CAM::read(bus, slot, function, 0x24, &device->prefetch_limit);
		IO::PCI::CAM::read(bus, slot, function, 0x26, &device->prefetch_base);
		IO::PCI::CAM::read(bus, slot, function, 0x28, &device->prefetch_base_upper);
		IO::PCI::CAM::read(bus, slot, function, 0x2C, &device->prefetch_limit_upper);
		IO::PCI::CAM::read(bus, slot, function, 0x30, &device->io_limit_upper);
		IO::PCI::CAM::read(bus, slot, function, 0x32, &device->io_base_upper);
		IO::PCI::CAM::read(bus, slot, function, 0x37, &device->capabilities_pointer);
		IO::PCI::CAM::read(bus, slot, function, 0x38, &device->expansion_address);
		IO::PCI::CAM::read(bus, slot, function, 0x3C, &device->bridge_control);
		IO::PCI::CAM::read(bus, slot, function, 0x3E, &device->interrupt_pin);
		IO::PCI::CAM::read(bus, slot, function, 0x3F, &device->interrupt_line);
	}
}

void IO::PCI::CAM::getCardBusBridgeDevice(uint_8 bus, uint_8 slot, uint_8 function, struct IO::PCI::CAM::CardBusBridgeDevice *device) {
	if (!IO::PCI::CAM::isValid(bus, slot, function))
		return;

	uint_8 type = 0x00;
	IO::PCI::CAM::getType(bus, slot, function, &type);
	if (type != 0x02)
		return;

	IO::PCI::CAM::getBasicDevice(bus, slot, function, device);

	if (device->header_type == 0x01) {
		IO::PCI::CAM::read(bus, slot, function, 0x10, &device->cardbus_base_address);
		IO::PCI::CAM::read(bus, slot, function, 0x14, &device->secondary_status);
		IO::PCI::CAM::read(bus, slot, function, 0x17, &device->capabilities_offset);
		IO::PCI::CAM::read(bus, slot, function, 0x18, &device->latency_timer);
		IO::PCI::CAM::read(bus, slot, function, 0x19, &device->subordinate_bus_number);
		IO::PCI::CAM::read(bus, slot, function, 0x1A, &device->cardbus_bus_number);
		IO::PCI::CAM::read(bus, slot, function, 0x1B, &device->pci_bus_number);
		IO::PCI::CAM::read(bus, slot, function, 0x1C, &device->memory_base_first);
		IO::PCI::CAM::read(bus, slot, function, 0x20, &device->memory_limit_first);
		IO::PCI::CAM::read(bus, slot, function, 0x24, &device->memory_base_second);
		IO::PCI::CAM::read(bus, slot, function, 0x28, &device->memory_limit_second);
		IO::PCI::CAM::read(bus, slot, function, 0x2C, &device->io_base_first);
		IO::PCI::CAM::read(bus, slot, function, 0x30, &device->io_limit_first);
		IO::PCI::CAM::read(bus, slot, function, 0x34, &device->io_base_second);
		IO::PCI::CAM::read(bus, slot, function, 0x38, &device->io_limit_second);
		IO::PCI::CAM::read(bus, slot, function, 0x3C, &device->bridge_control);
		IO::PCI::CAM::read(bus, slot, function, 0x3E, &device->interrupt_pin);
		IO::PCI::CAM::read(bus, slot, function, 0x3F, &device->interrupt_line);
		IO::PCI::CAM::read(bus, slot, function, 0x40, &device->subsystem_vendor);
		IO::PCI::CAM::read(bus, slot, function, 0x42, &device->subsystem_id);
		IO::PCI::CAM::read(bus, slot, function, 0x44, &device->legacy_base_address);
	}
}

bool IO::PCI::Device::hasFunctions(uint_8 bus, uint_8 slot) {
	uint_8 res = 0x00;
	IO::PCI::CAM::read(bus, slot, 0, 0x0E, &res);

	return (res & (1 << 7));
}

bool IO::PCI::Device::isValid(uint_8 bus, uint_8 slot, uint_8 cFunc) {
	uint_16 vId = 0x0000;

	if (!IO::PCI::CAM::isValid(bus, slot, cFunc))
		return false;

	IO::PCI::CAM::getVendor(bus, slot, 0, &vId);
	if (!(vId != 0xFFFF && vId != 0x0000))
		return false;

	return true;
}

void IO::PCI::Device::detect(void forEachDevice(IO::PCI::CAM::BasicDevice *, int)) {
	int ind = 0;

	for (int bus = 0; bus < 256; bus++) {
		for (int slot = 0; slot < 32; slot++) {
			int totFunc = IO::PCI::Device::hasFunctions(bus, slot) ? 8 : 1;

			for (int function = 0; function < totFunc; function++) {
				if (IO::PCI::Device::isValid(bus, slot, function)) {
					IO::PCI::CAM::BasicDevice device;
					IO::PCI::CAM::getBasicDevice(bus, slot, function, &device);
					forEachDevice(&device, ind);
					ind++;
				}
			}
		}
	}
}