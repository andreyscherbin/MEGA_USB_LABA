/*
 * ConfigurationDescriptor.h
 *
 *  Created on: 8 мая 2021 г.
 *      Author: root
 */
#include <string.h>
#include <iostream>
#include <bits/stdc++.h>
#include "InterfaceDescriptor.h"

#ifndef CONFIGURATIONDESCRIPTOR_H_
#define CONFIGURATIONDESCRIPTOR_H_

namespace std {

class ConfigurationDescriptor {
public:
	ConfigurationDescriptor() {
	}
	virtual ~ConfigurationDescriptor() {
	}

	uint8_t getBConfigurationValue() const {
		return bConfigurationValue;
	}

	void setBConfigurationValue(uint8_t bConfigurationValue) {
		this->bConfigurationValue = bConfigurationValue;
	}

	uint8_t getBDescriptorType() const {
		return bDescriptorType;
	}

	void setBDescriptorType(uint8_t bDescriptorType) {
		this->bDescriptorType = bDescriptorType;
	}

	uint8_t getBLength() const {
		return bLength;
	}

	void setBLength(uint8_t bLength) {
		this->bLength = bLength;
	}

	uint8_t getBmAttributes() const {
		return bmAttributes;
	}

	void setBmAttributes(uint8_t bmAttributes) {
		this->bmAttributes = bmAttributes;
	}

	uint8_t getBMaxPower() const {
		return bMaxPower;
	}

	void setBMaxPower(uint8_t bMaxPower) {
		this->bMaxPower = bMaxPower;
	}

	uint8_t getBNumInterfaces() const {
		return bNumInterfaces;
	}

	void setBNumInterfaces(uint8_t bNumInterfaces) {
		this->bNumInterfaces = bNumInterfaces;
	}

	uint8_t getIConfiguration() const {
		return iConfiguration;
	}

	void setIConfiguration(uint8_t iConfiguration) {
		this->iConfiguration = iConfiguration;
	}

	uint16_t getWTotalLength() const {
		return wTotalLength;
	}

	void setWTotalLength(uint16_t wTotalLength) {
		this->wTotalLength = wTotalLength;
	}

	vector<InterfaceDescriptor>& getInterfaceDescriptors() {
		return interfaceDescriptors;
	}

	void setInterfaceDescriptors(
			vector<InterfaceDescriptor> &interfaceDescriptors) {
		this->interfaceDescriptors = interfaceDescriptors;
	}

private:
	vector<InterfaceDescriptor> interfaceDescriptors;
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t wTotalLength;
	uint8_t bNumInterfaces;
	uint8_t bConfigurationValue;
	uint8_t iConfiguration;
	uint8_t bmAttributes;
	uint8_t bMaxPower;
};

}

#endif /* CONFIGURATIONDESCRIPTOR_H_ */
