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

#ifndef PCI_H
#define PCI_H

#include "../../common/common.hpp"
#include "../io.hpp"

namespace IO {
	namespace PCI {
		namespace Class {
			class Basic {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 NON_VGA_DISPLAY_DEVICE;
				static const uint_8 VGA_DISPLAY_DEVICE;
			};

			class Storage {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 SCSI_BUS_CONTROLLER;
				static const uint_8 IDE_CONTROLLER;
				static const uint_8 FLOPPY_DISK_CONTROLLER;
				static const uint_8 IPI_BUS_CONTROLLER;
				static const uint_8 RAID_CONTROLLER;
				static const uint_8 ATA_CONTROLLER;
				static const uint_8 SERIAL_ATA_CONTROLLER;
				static const uint_8 SERIAL_ATTACHED_SCSI_CONTROLLER;
				static const uint_8 OTHER_STORAGE_CONTROLLER;
			};

			class Network {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 ETHERNET_CONTROLLER;
				static const uint_8 TOKEN_RING_CONTROLLER;
				static const uint_8 FDDI_CONTROLLER;
				static const uint_8 ATM_CONTROLLER;
				static const uint_8 ISDN_CONTROLLER;
				static const uint_8 WORLDFIP_CONTROLLER;
				static const uint_8 PICMG_MULTI_COMPUTING_CONTROLLER;
				static const uint_8 OTHER_NETWORK_CONTROLLER;
			};

			class Display {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 DISPLAY_CONTROLLER;
				static const uint_8 DXGA_CONTROLLER;
				static const uint_8 D3D_CONTROLLER;
				static const uint_8 OTHER_DISPLAY_CONTROLLER;
			};

			class Multimedia {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 VIDEO_DEVICE;
				static const uint_8 AUDIO_DEVICE;
				static const uint_8 COMPUTER_TELEPHONY_DEVICE;
				static const uint_8 OTHER_MULTIMEDIA_DEVICE;
			};

			class Memory {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 RAM_CONTROLLER;
				static const uint_8 FLASH_CONTROLLER;
				static const uint_8 OTHER_MEMORY_CONTROLLER;
			};

			class Bridge {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 HOST_BRIDGE;
				static const uint_8 ISA_BRIDGE;
				static const uint_8 EISA_BRIDGE;
				static const uint_8 MCA_BRIDGE;
				static const uint_8 PCI_BRIDGE;
				static const uint_8 PCMCIA_BRIDGE;
				static const uint_8 NUBUS_BRIDGE;
				static const uint_8 CARDBUS_BRIDGE;
				static const uint_8 RACEWAY_BRIDGE;
				static const uint_8 PCI_BRIDGE_SEMI_TRANSPARENT;
				static const uint_8 INFINIBRAND_BRIDGE;
				static const uint_8 OTHER_BRIDGE_DEVICE;
			};

			class Communication {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 XT_SERIAL_CONTROLLER;
				static const uint_8 PARALLEL_PORT;
				static const uint_8 MULTIPORT_SERIAL_CONTROLLER;
				static const uint_8 GENERIC_MODEM;
				static const uint_8 IEEE_CONTROLLER;
				static const uint_8 SMART_CARD;
				static const uint_8 OTHER_COMMUNICATION_DEVICE;
			};

			namespace Peripheral {
				class System {
				public:
					static const uint_8 CLASS_CODE;
					static const uint_8 PIC;
					static const uint_8 DMA_CONTROLLER;
					static const uint_8 SYSTEM_TIMER;
					static const uint_8 RTC_CONTROLLER;
					static const uint_8 PCI_HOTPLUG_CONTROLLER;
					static const uint_8 OTHER_SYSTEM_PERIPHERAL;
				};

				class User {
				public:
					static const uint_8 CLASS_CODE;
					static const uint_8 KEYBOARD_CONTROLLER;
					static const uint_8 DIGITIZER;
					static const uint_8 MOUSE_CONTROLLER;
					static const uint_8 SCANNER_CONTROLLER;
					static const uint_8 GAMEPORT_CONTROLLER;
					static const uint_8 OTHER_INPUT_CONTROLLER;
				};
			};

			class Docker {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 GENERIC_DOCKING_STATION;
				static const uint_8 OTHER_DOCKING_STATION;
			};

			class Processor {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 I386_PROCESSOR;
				static const uint_8 I486_PROCESSOR;
				static const uint_8 PENTIUM_PROCESSOR;
				static const uint_8 ALPHA_PROCESSOR;
				static const uint_8 POWERPC_PROCESSOR;
				static const uint_8 MIPS_PROCESSOR;
				static const uint_8 CO_PROCESSOR;
			};

			class SerialBus {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 IEEE_1394_BUS;
				static const uint_8 ACCESS_BUS;
				static const uint_8 SSA_BUS;
				static const uint_8 USB_BUS;
				static const uint_8 FIBRE_CHANNEL_BUS;
				static const uint_8 SM_BUS;
				static const uint_8 INFINIBAND_BUS;
				static const uint_8 IPMI_SMIC_BUS;
				static const uint_8 SERCOS_BUS;
				static const uint_8 CAN_BUS;
			};

			class Wireless {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 IRDA_CONTROLLER;
				static const uint_8 CONSUMER_IR_CONTROLLER;
				static const uint_8 RF_CONTROLLER;
				static const uint_8 BLUETOOTH_CONTROLLER;
				static const uint_8 BROADBAND_CONTROLLER;
				static const uint_8 ETHERNET_CONTROLLER_A;
				static const uint_8 ETHERNET_CONTROLLER_B;
				static const uint_8 OTHER_WIRELESS_CONTROLLER;
			};

			class IntelligentIO {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 FIFO_MESSAGE;
				static const uint_8 I20_ARCHITECTURE;
			};

			class Satellite {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 TV_CONTROLLER;
				static const uint_8 AUDIO_CONTROLLER;
				static const uint_8 VOICE_CONTROLLER;
				static const uint_8 DATA_CONTROLLER;
			};

			class Cryptography {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 NETWORK_CRYPTOGRAPHY_CONTROLLER;
				static const uint_8 ENTERTAINMENT_CRYPTOGRAPHY_CONTROLLER;
				static const uint_8 OTHER_CRYPTOGRAPHY_CONTROLLER;
			};

			class Acquisition {
			public:
				static const uint_8 CLASS_CODE;
				static const uint_8 DPIO_MODULE;
				static const uint_8 PERFORMANCE_COUNTER;
				static const uint_8 CSPT_METER;
				static const uint_8 MANAGEMENT_CARD;
				static const uint_8 OTHER_ACQUISITION_CONTROLLER;
			};
		};
		
		class CAM {
		public:
			struct BasicDevice {
				uint_8 bus;
				uint_8 slot;
				uint_8 function;

				uint_16 device_id;
				uint_16 vendor_id;
				uint_16 status;
				uint_16 command;
				uint_8 class_code;
				uint_8 subclass;
				uint_8 prog_if;
				uint_8 revision_id;
				uint_8 bist;
				uint_8 header_type;
				uint_8 latency_timer;
				uint_8 cache_line_size;
			};

			struct CommonDevice : BasicDevice {
				uint_32 bar0;
				uint_32 bar1;
				uint_32 bar2;
				uint_32 bar3;
				uint_32 bar4;
				uint_32 bar5;
				uint_32 cis_pointer;
				uint_16 subsystem_id;
				uint_16 subsystem_vendor;
				uint_32 expansion_address;
				uint_8 capabilities_pointer;
				uint_8 max_latency;
				uint_8 min_grant;
				uint_8 interrupt_pin;
				uint_8 interrupt_line;
			};

			struct BridgeDevice : BasicDevice {
				uint_32 bar0;
				uint_32 bar1;
				uint_8 secondary_latency_timer;
				uint_8 subordinate_bus_number;
				uint_8 secondary_bus_number;
				uint_8 primary_bus_number;
				uint_16 secondary_status;
				uint_8 io_limit;
				uint_8 io_base;
				uint_16 memory_limit;
				uint_16 memory_base;
				uint_16 prefetch_limit;
				uint_16 prefetch_base;
				uint_32 prefetch_base_upper;
				uint_32 prefetch_limit_upper;
				uint_16 io_base_upper;
				uint_16 io_limit_upper;
				uint_8 capabilities_pointer;
				uint_32 expansion_address;
				uint_16 bridge_control;
				uint_8 interrupt_pin;
				uint_8 interrupt_line;
			};

			struct CardBusBridgeDevice : BasicDevice {
				uint_32 cardbus_base_address;
				uint_16 secondary_status;
				uint_8 capabilities_offset;
				uint_8 latency_timer;
				uint_8 subordinate_bus_number;
				uint_8 cardbus_bus_number;
				uint_8 pci_bus_number;
				uint_32 memory_base_first;
				uint_32 memory_limit_first;
				uint_32 memory_base_second;
				uint_32 memory_limit_second;
				uint_32 io_base_first;
				uint_32 io_limit_first;
				uint_32 io_base_second;
				uint_32 io_limit_second;
				uint_16 bridge_control;
				uint_8 interrupt_pin;
				uint_8 interrupt_line;
				uint_16 subsystem_vendor;
				uint_16 subsystem_id;
				uint_32 legacy_base_address;
			};

			static void select(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg);
			static void read(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_8 *val);
			static void read(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_16 *val);
			static void read(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_32 *val);
			static void write(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_8 val);
			static void write(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_16 val);
			static void write(uint_8 bus, uint_8 slot, uint_8 function, uint_8 reg, uint_32 val);
			static void getType(uint_8 bus, uint_8 slot, uint_8 function, uint_8 *type);
			static void getVendor(uint_8 bus, uint_8 slot, uint_8 function, uint_16 *vendor);
			static bool isValid(uint_8 bus, uint_8 slot, uint_8 function);
			static void getBasicDevice(uint_8 bus, uint_8 slot, uint_8 function, struct IO::PCI::CAM::BasicDevice *device);
			static void getCommonDevice(uint_8 bus, uint_8 slot, uint_8 function, struct IO::PCI::CAM::CommonDevice *device);
			static void getBridgeDevice(uint_8 bus, uint_8 slot, uint_8 function, struct IO::PCI::CAM::BridgeDevice *device);
			static void getCardBusBridgeDevice(uint_8 bus, uint_8 slot, uint_8 function, struct IO::PCI::CAM::CardBusBridgeDevice *device);

			static IO::Port *command_port;
			static IO::Port *data_port;
		};

		class Device {
		public:
			static bool hasFunctions(uint_8 bus, uint_8 device);
			static bool isValid(uint_8 bus, uint_8 device, uint_8 cFunc);
			static void detect(void (IO::PCI::CAM::BasicDevice *, int));
		};
	};
};

#endif