/*
 * The driver manager, for devices such as PCI or keyboard.
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

#ifndef DEVICE_H
#define DEVICE_H

#include "../../common/common.hpp"

#define DEVICE_MANAGER_MAX_DRIVERS 512

namespace IO {
	class Driver {
	public:
		Driver();
		~Driver();

		virtual bool isEnabled();
		virtual bool isStarted();
		virtual char* getVendorName();
		virtual char* getProductName();

		virtual int enable();
		virtual int disable();

		virtual int start();
		virtual int restart();
		virtual int stop();
	};

	class DriverManager {
	private:
		static Driver *driverList[DEVICE_MANAGER_MAX_DRIVERS];
		static int driverCount;

	public:
		static int get(Driver *index);
		static Driver *get(int index);

		static int add(Driver *driver);
		static int remove(Driver *driver);
		static int remove(int index);

		static int enable(Driver *driver);
		static int enable(int driver);

		static int disable(Driver *driver);
		static int disable(int driver);

		static void enableAll(int *res);
		static void disableAll(int *res);

		static void startAll(int *res);
		static void stopAll(int *res);

		static int getCount();
	};
};

#endif