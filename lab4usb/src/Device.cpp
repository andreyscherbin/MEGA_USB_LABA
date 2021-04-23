/*
 * Device.cpp
 *
 *  Created on: 23 апр. 2021 г.
 *      Author: dmitriy
 */

#include "Device.h"

namespace std {

Device::Device() {
	// TODO Auto-generated constructor stub

}

Device::~Device() {
	// TODO Auto-generated destructor stub
}

uint8_t Device::get_bus_number() {
	return bus_number;
}

uint8_t Device::get_device_number() {
	return device_number;
}

string Device::get_type() {
	return type;
}

string Device::get_decryption() {
	return decryption;
}

uint16_t Device::get_id_product() {
	return idProduct;
}

uint16_t Device::get_id_vendor() {
	return idVendor;
}

uint16_t Device::get_class_device() {
	return class_device;
}
uint16_t Device::get_subclass_device() {

	return subclass_device;
}
uint16_t Device::get_protocol_device() {

	return protocol_device;
}
uint16_t Device::get_class_interface() {

	return class_interface;
}
uint16_t Device::get_subclass_interface() {

	return subclass_interface;
}
uint16_t Device::get_protocol_interface() {

	return protocol_interface;
}

void Device::set_bus_number(uint8_t bus_number) {
	this->bus_number = bus_number;
}
void Device::set_device_number(uint8_t device_number) {
	this->device_number = device_number;
}

void Device::set_type(string type) {
	this->type = type;
}

void Device::set_decryption(string decryption) {
	this->decryption = decryption;
}

void Device::set_id_product(uint16_t idProduct) {
	this->idProduct = idProduct;
}
void Device::set_id_vendor(uint16_t idVendor) {
	this->idVendor = idVendor;
}
void Device::set_class_device(uint16_t class_device) {
	this->class_device = class_device;
}
void Device::set_subclass_device(uint16_t subclass_device) {
	this->subclass_device = subclass_device;
}
void Device::set_protocol_device(uint16_t protocol_device) {
	this->protocol_device = protocol_device;
}
void Device::set_class_interface(uint16_t class_interface) {
	this->class_interface = class_interface;
}
void Device::set_subclass_interface(uint16_t subclass_interface) {
	this->subclass_interface = subclass_interface;
}
void Device::set_protocol_interface(uint16_t protocol_interface) {
	this->protocol_interface = protocol_interface;
}

} /* namespace std */
