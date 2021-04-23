/*
 * Device.h
 *
 *  Created on: 23 апр. 2021 г.
 *      Author: dmitriy
 */
#include <string.h>
#include <iostream>

#ifndef DEVICE_H_
#define DEVICE_H_

namespace std {

class Device {
public:
	Device();
	virtual ~Device();
	string get_type();
	string get_decryption();
	uint16_t get_id_product();
	uint16_t get_id_vendor();
	uint16_t get_class_device();
	uint16_t get_subclass_device();
	uint16_t get_protocol_device();
	uint16_t get_class_interface();
	uint16_t get_subclass_interface();
	uint16_t get_protocol_interface();
	uint8_t get_bus_number();
	uint8_t get_device_number();
	void set_type(string type);
	void set_decryption(string decryption);
	void set_id_product(uint16_t idProduct);
	void set_id_vendor(uint16_t idVendor);
	void set_class_device(uint16_t class_device);
	void set_subclass_device(uint16_t subclass_device);
	void set_protocol_device(uint16_t protocol_device);
	void set_class_interface(uint16_t class_interface);
	void set_subclass_interface(uint16_t subclass_interface);
	void set_protocol_interface(uint16_t protocol_interface);
	void set_bus_number(uint8_t bus_number);
	void set_device_number(uint8_t device_number);
private:
	// Data Members
	uint16_t idProduct;
	uint16_t idVendor;
	uint16_t class_device;
	uint16_t subclass_device;
	uint16_t protocol_device;
	uint16_t class_interface;
	uint16_t subclass_interface;
	uint16_t protocol_interface;
	string type;
	string decryption;
	uint8_t bus_number;
	uint8_t device_number;
};

} /* namespace std */

#endif /* DEVICE_H_ */
