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

#include "driver.hpp"

#include "../../common/common.hpp"


IO::Driver* IO::DriverManager::driverList[DEVICE_MANAGER_MAX_DRIVERS];
int IO::DriverManager::driverCount = 0;

int IO::DriverManager::get(Driver *driver) {
	for (int i = 0; i < IO::DriverManager::driverCount; i++) {
		if (IO::DriverManager::driverList[i] == driver)
			return i;
	}

	return -1;
}

IO::Driver* IO::DriverManager::get(int index) {
	for (int i = 0; i < IO::DriverManager::driverCount; i++) {
		if (i == index)
			return IO::DriverManager::driverList[i];
	}

	return nullptr;
}

int IO::DriverManager::add(IO::Driver *driver) {
	if (IO::DriverManager::driverCount == DEVICE_MANAGER_MAX_DRIVERS)
		return -1;

	IO::DriverManager::driverList[IO::DriverManager::driverCount] = driver;

	int res = 0;
	res = IO::DriverManager::driverList[IO::DriverManager::driverCount]->enable();
	if (res < 0)
		return res;
	res = IO::DriverManager::driverList[IO::DriverManager::driverCount]->start();
	if (res < 0)
		return res;

	IO::DriverManager::driverCount++;

	return res;
}

int IO::DriverManager::remove(IO::Driver *driver) {
	for (int i = 0; i < IO::DriverManager::driverCount; i++) {
		if (IO::DriverManager::driverList[i] == driver) {
			int ores = 0;
			int res = IO::DriverManager::driverList[i]->stop();
			ores = res;
			res = IO::DriverManager::driverList[i]->disable();

			IO::DriverManager::driverList[i] = nullptr;

			for (int j = i; j < IO::DriverManager::driverCount; j++) {
				if (j < IO::DriverManager::driverCount)
					IO::DriverManager::driverList[i] = IO::DriverManager::driverList[j + 1];
			}

			IO::DriverManager::driverList[IO::DriverManager::driverCount] = nullptr;
			IO::DriverManager::driverCount--;

			if (ores < 0)
				return ores;
			else if (res < 0)
				return res;
		}
	}

	return -1;
}

int IO::DriverManager::remove(int index) {
	Driver* ind = IO::DriverManager::get(index);

	if (ind == nullptr)
		return -1;

	return IO::DriverManager::remove(ind);
}

int IO::DriverManager::enable(Driver *driver) {
	int ind = IO::DriverManager::get(driver);

	if (ind < 0 || driver->isEnabled())
		return -1;

	return IO::DriverManager::driverList[ind]->enable();
}

int IO::DriverManager::enable(int driver) {
	Driver* ind = IO::DriverManager::get(driver);

	if (ind == nullptr || ind->isEnabled())
		return -1;

	return IO::DriverManager::enable(ind);
}

int IO::DriverManager::disable(Driver *driver) {
	int ind = IO::DriverManager::get(driver);

	if (ind < 0 || !driver->isEnabled())
		return -1;

	return IO::DriverManager::driverList[ind]->disable();
}

int IO::DriverManager::disable(int driver) {
	Driver *ind = IO::DriverManager::get(driver);

	if (ind == nullptr || !ind->isEnabled())
		return -1;

	return IO::DriverManager::disable(ind);
}

void IO::DriverManager::enableAll(int *res) {
	for (int i = 0; i < IO::DriverManager::driverCount; i++)
		if (!IO::DriverManager::driverList[i]->isEnabled())
			res[i] = IO::DriverManager::driverList[i]->enable();
}

void IO::DriverManager::disableAll(int *res) {
	for (int i = 0; i < IO::DriverManager::driverCount; i++)
		if (IO::DriverManager::driverList[i]->isEnabled())
			res[i] = IO::DriverManager::driverList[i]->disable();
}

void IO::DriverManager::startAll(int *res) {
	for (int i = 0; i < IO::DriverManager::driverCount; i++)
		if (!IO::DriverManager::driverList[i]->isStarted())
			res[i] = IO::DriverManager::driverList[i]->start();
}

void IO::DriverManager::stopAll(int *res) {
	for (int i = 0; i < IO::DriverManager::driverCount; i++)
		if (IO::DriverManager::driverList[i]->isStarted())
			res[i] = IO::DriverManager::driverList[i]->stop();
}

int IO::DriverManager::getCount() {
	return IO::DriverManager::driverCount;
}