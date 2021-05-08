/*
 * InterfaceDescriptor.h
 *
 *  Created on: 8 мая 2021 г.
 *      Author: root
 */

#include <string.h>
#include <iostream>
#include "EndpointDescriptor.h"

#ifndef INTERFACEDESCRIPTOR_H_
#define INTERFACEDESCRIPTOR_H_

namespace std {

class InterfaceDescriptor {
public:
	InterfaceDescriptor() {
	}
	;
	virtual ~InterfaceDescriptor() {
	}
	;

	uint8_t getBAlternateSetting() const {
		return bAlternateSetting;
	}

	void setBAlternateSetting(uint8_t bAlternateSetting) {
		this->bAlternateSetting = bAlternateSetting;
	}

	uint8_t getBDescriptorType() const {
		return bDescriptorType;
	}

	void setBDescriptorType(uint8_t bDescriptorType) {
		this->bDescriptorType = bDescriptorType;
	}

	uint8_t getBInterfaceClass() const {
		return bInterfaceClass;
	}

	void setBInterfaceClass(uint8_t bInterfaceClass) {
		this->bInterfaceClass = bInterfaceClass;
	}

	uint8_t getBInterfaceNumber() const {
		return bInterfaceNumber;
	}

	void setBInterfaceNumber(uint8_t bInterfaceNumber) {
		this->bInterfaceNumber = bInterfaceNumber;
	}

	uint8_t getBInterfaceProtocol() const {
		return bInterfaceProtocol;
	}

	void setBInterfaceProtocol(uint8_t bInterfaceProtocol) {
		this->bInterfaceProtocol = bInterfaceProtocol;
	}

	uint8_t getBInterfaceSubClass() const {
		return bInterfaceSubClass;
	}

	void setBInterfaceSubClass(uint8_t bInterfaceSubClass) {
		this->bInterfaceSubClass = bInterfaceSubClass;
	}

	uint8_t getBLength() const {
		return bLength;
	}

	void setBLength(uint8_t bLength) {
		this->bLength = bLength;
	}

	uint8_t getBNumEndpoints() const {
		return bNumEndpoints;
	}

	void setBNumEndpoints(uint8_t bNumEndpoints) {
		this->bNumEndpoints = bNumEndpoints;
	}

	uint8_t getIInterface() const {
		return iInterface;
	}

	void setIInterface(uint8_t iInterface) {
		this->iInterface = iInterface;
	}

	vector<EndpointDescriptor>& getEndpointDescriptors() {
		return endpointDescriptors;
	}

	void setEndpointDescriptors(
			vector<EndpointDescriptor> &endpointDescriptors) {
		this->endpointDescriptors = endpointDescriptors;
	}

private:
	vector<EndpointDescriptor> endpointDescriptors;
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bInterfaceNumber;
	uint8_t bAlternateSetting;
	uint8_t bNumEndpoints;
	uint8_t bInterfaceClass;
	uint8_t bInterfaceSubClass;
	uint8_t bInterfaceProtocol;
	uint8_t iInterface;
};
}

#endif /* INTERFACEDESCRIPTOR_H_ */
