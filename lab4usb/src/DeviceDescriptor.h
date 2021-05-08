/*
 * DeviceDescriptor.h
 *
 *  Created on: 8 мая 2021 г.
 *      Author: root
 */

#include <vector>
#include <string>
#include "ConfigurationDescriptor.h"

#ifndef DEVICEDESCRIPTOR_H_
#define DEVICEDESCRIPTOR_H_

namespace std {

class DeviceDescriptor {
public:
	DeviceDescriptor() {
	}
	virtual ~DeviceDescriptor() {
	}

	uint16_t getBcdDevice() const {
		return bcdDevice;
	}

	void setBcdDevice(uint16_t bcdDevice) {
		this->bcdDevice = bcdDevice;
	}

	uint16_t getBcdUsb() const {
		return bcdUSB;
	}

	void setBcdUsb(uint16_t bcdUsb) {
		bcdUSB = bcdUsb;
	}

	uint8_t getBDescriptorType() const {
		return bDescriptorType;
	}

	void setBDescriptorType(uint8_t bDescriptorType) {
		this->bDescriptorType = bDescriptorType;
	}

	uint8_t getBDeviceClass() const {
		return bDeviceClass;
	}

	void setBDeviceClass(uint8_t bDeviceClass) {
		this->bDeviceClass = bDeviceClass;
	}

	uint8_t getBDeviceProtocol() const {
		return bDeviceProtocol;
	}

	void setBDeviceProtocol(uint8_t bDeviceProtocol) {
		this->bDeviceProtocol = bDeviceProtocol;
	}

	uint8_t getBDeviceSubClass() const {
		return bDeviceSubClass;
	}

	void setBDeviceSubClass(uint8_t bDeviceSubClass) {
		this->bDeviceSubClass = bDeviceSubClass;
	}

	uint8_t getBLength() const {
		return bLength;
	}

	void setBLength(uint8_t bLength) {
		this->bLength = bLength;
	}

	uint8_t getBMaxPacketSize0() const {
		return bMaxPacketSize0;
	}

	void setBMaxPacketSize0(uint8_t bMaxPacketSize0) {
		this->bMaxPacketSize0 = bMaxPacketSize0;
	}

	uint8_t getBNumConfigurations() const {
		return bNumConfigurations;
	}

	void setBNumConfigurations(uint8_t bNumConfigurations) {
		this->bNumConfigurations = bNumConfigurations;
	}

	uint16_t getIdProduct() const {
		return idProduct;
	}

	void setIdProduct(uint16_t idProduct) {
		this->idProduct = idProduct;
	}

	uint16_t getIdVendor() const {
		return idVendor;
	}

	void setIdVendor(uint16_t idVendor) {
		this->idVendor = idVendor;
	}

	uint8_t getIManufacturer() const {
		return iManufacturer;
	}

	void setIManufacturer(uint8_t iManufacturer) {
		this->iManufacturer = iManufacturer;
	}

	uint8_t getIProduct() const {
		return iProduct;
	}

	void setIProduct(uint8_t iProduct) {
		this->iProduct = iProduct;
	}

	uint8_t getISerialNumber() const {
		return iSerialNumber;
	}

	void setISerialNumber(uint8_t iSerialNumber) {
		this->iSerialNumber = iSerialNumber;
	}

	vector<ConfigurationDescriptor>& getConfigurationDescriptors() {
		return configurationDescriptors;
	}

	void setConfigurationDescriptors(
			vector<ConfigurationDescriptor> &configurationDescriptors) {
		this->configurationDescriptors = configurationDescriptors;
	}

private:
	vector<ConfigurationDescriptor> configurationDescriptors;
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdUSB;
	uint8_t bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize0;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t iManufacturer;
	uint8_t iProduct;
	uint8_t iSerialNumber;
	uint8_t bNumConfigurations;
};

} /* namespace std */

#endif /* DEVICEDESCRIPTOR_H_ */
