/*
 * EndpointDescriptor.h
 *
 *  Created on: 8 мая 2021 г.
 *      Author: root
 */

#include <string.h>
#include <iostream>

#ifndef ENDPOINTDESCRIPTOR_H_
#define ENDPOINTDESCRIPTOR_H_

namespace std {

class EndpointDescriptor {
public:
	EndpointDescriptor() {
	}
	;
	virtual ~EndpointDescriptor() {
	}
	;

	uint8_t getBDescriptorType() const {
		return bDescriptorType;
	}

	void setBDescriptorType(uint8_t bDescriptorType) {
		this->bDescriptorType = bDescriptorType;
	}

	uint8_t getBEndpointAddress() const {
		return bEndpointAddress;
	}

	void setBEndpointAddress(uint8_t bEndpointAddress) {
		this->bEndpointAddress = bEndpointAddress;
	}

	uint8_t getBInterval() const {
		return bInterval;
	}

	void setBInterval(uint8_t bInterval) {
		this->bInterval = bInterval;
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

	uint16_t getWMaxPacketSize() const {
		return wMaxPacketSize;
	}

	void setWMaxPacketSize(uint16_t wMaxPacketSize) {
		this->wMaxPacketSize = wMaxPacketSize;
	}

private:
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
};

} /* namespace std */

#endif /* ENDPOINTDESCRIPTOR_H_ */
