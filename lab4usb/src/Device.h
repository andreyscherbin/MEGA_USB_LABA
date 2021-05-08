/*
 * Device.h
 *
 *  Created on: 23 апр. 2021 г.
 *      Author: dmitriy
 */


#include "DeviceDescriptor.h"


#ifndef DEVICE_H_
#define DEVICE_H_

namespace std {

class Device {
public:
	Device() {}
	virtual ~Device() {}


	uint8_t getBusNumber() const {
		return bus_number;
	}

	void setBusNumber(uint8_t busNumber) {
		bus_number = busNumber;
	}

	uint8_t getDeviceNumber() const {
		return device_number;
	}

	void setDeviceNumber(uint8_t deviceNumber) {
		device_number = deviceNumber;
	}

	const DeviceDescriptor& getDeviceDescriptor() const {
		return deviceDescriptor;
	}

	void setDeviceDescriptor(const DeviceDescriptor &deviceDescriptor) {
		this->deviceDescriptor = deviceDescriptor;
	}

	const string& getType() const {
		return type;
	}

	void setType(const string &type) {
		this->type = type;
	}

	const string& getProduct() const {
		return product;
	}

	void setProduct(const string &product) {
		this->product = product;
	}

	const string& getVendor() const {
		return vendor;
	}

	void setVendor(const string &vendor) {
		this->vendor = vendor;
	}

private:
	DeviceDescriptor deviceDescriptor;
	string type;
	string vendor;
	string product;
	uint8_t bus_number;
	uint8_t device_number;
};

} /* namespace std */

#endif /* DEVICE_H_ */
