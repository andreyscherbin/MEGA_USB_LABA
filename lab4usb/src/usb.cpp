#include <string.h>
#include <libusb-1.0/libusb.h>
#include <iostream>
#include "Device.h"
#include <bits/stdc++.h>
#include <regex>

using namespace std;

/*
 #define USB_DEVICE_CLASS_RESERVED           0x00
 #define USB_DEVICE_CLASS_COMMUNICATIONS     0x02
 #define USB_DEVICE_CLASS_MONITOR            0x04
 #define USB_DEVICE_CLASS_PHYSICAL_INTERFACE 0x05
 #define USB_DEVICE_CLASS_POWER              0x06
 #define USB_DEVICE_CLASS_PRINTER            0x07
 #define USB_DEVICE_CLASS_STORAGE            0x08
 #define USB_DEVICE_CLASS_HUB                0x09
 #define USB_DEVICE_CLASS_VENDOR_SPECIFIC    0xFF

 #define USB_DEVICE_CLASS_HUMAN_INTERFACE    0x03
 #define USB_DEVICE_PROTOCOL_KEYBOARD        0x01
 #define USB_DEVICE_PROTOCOL_MOUSE           0x02

 #define USB_DEVICE_CLASS_AUDIO              0x01
 #define USB_DEVICE_SUBCLASS_HEADPHONES      0x02

 #define USB_DEVICE_CLASS_STORAGE            0x08
 */

void create_devices(libusb_device *dev, vector<Device> &devices);
string decryption(uint16_t idVendor, uint16_t idProduct);

int main(int argc, char *argv[]) {

	vector<Device> devices;
	libusb_context *context = NULL;
	libusb_device **devs = NULL;
	int r; //for return values

	r = libusb_init(&context); //initialize a library session
	if (r < 0) {
		cout << "Init Error " << r << endl; //there was an error
		return 1;
	}

	libusb_set_debug(context, 3);
	ssize_t count_new = libusb_get_device_list(context, &devs);
	if (count_new < 0) {
		cout << "Get Device Error" << endl; //there was an error
	}

	cout << count_new << " Devices in list." << endl; //print total number of usb devices
	ssize_t i; 	//for iterating through the list

	for (i = 0; i < count_new; i++) {
		create_devices(devs[i], devices); //print specs of this device
	}

	for (int i = 0; i < devices.size(); i++) {
		printf("Bus %03u Device %03u: ID %04x:%04x %s\n",
				devices[i].get_bus_number(), devices[i].get_device_number(),
				devices[i].get_id_vendor(), devices[i].get_id_product(),
				devices[i].get_decryption().c_str());
	}

	//Этот код попытка вытащить еще больше информации из usb, если захочешь lsusb -v реализовать.
	/*for (i = 0; i < count_new; i++) {

	 libusb_device *device = list[i];
	 libusb_device_descriptor desc = { 0 };

	 libusb_get_device_descriptor(device, &desc);
	 libusb_get_device_address(device);
	 libusb_get_port_number(device);

	 libusb_device_handle *handle = libusb_open_device_with_vid_pid(
	 NULL, desc.idVendor, desc.idProduct);
	 if (handle != NULL) {
	 libusb_config_descriptor *config_descriptor = { 0 };
	 libusb_get_active_config_descriptor(device, &config_descriptor);

	 uint8_t bInterfaceClass =
	 config_descriptor->interface[0].altsetting[0].bInterfaceClass;
	 uint8_t bInterfaceSubClass =
	 config_descriptor->interface[0].altsetting[0].bInterfaceSubClass;
	 uint8_t bInterfaceProtocol =
	 config_descriptor->interface[0].altsetting[0].bInterfaceProtocol;

	 string type_device;

	 switch (desc.bDeviceClass) {
	 case USB_DEVICE_CLASS_AUDIO:
	 type_device = "AUDIO_DEVICE";
	 break;
	 case USB_DEVICE_CLASS_COMMUNICATIONS:
	 type_device = "COMMUNICATIONS_DEVICE";
	 break;
	 case USB_DEVICE_CLASS_HUMAN_INTERFACE:
	 type_device = "HUMAN_INTERFACE_DEVICE";
	 break;
	 case USB_DEVICE_CLASS_MONITOR:
	 type_device = "MONITOR_DEVICE";
	 break;
	 case USB_DEVICE_CLASS_PHYSICAL_INTERFACE:
	 type_device = "PHYSICAL_INTERFACE";
	 break;
	 case USB_DEVICE_CLASS_POWER:
	 type_device = "POWER";
	 break;
	 case USB_DEVICE_CLASS_PRINTER:
	 type_device = "PRINTER";
	 break;
	 case USB_DEVICE_CLASS_STORAGE:
	 type_device = "STORAGE";
	 break;
	 case USB_DEVICE_CLASS_HUB:
	 type_device = "HUB";
	 break;
	 case 0:
	 if (bInterfaceClass == 0x08) {
	 type_device = "STORAGE";
	 }
	 if (bInterfaceClass == 0x03) {
	 if (bInterfaceProtocol == 0x01) {
	 type_device = "KEYBOARD";
	 }
	 if (bInterfaceProtocol == 0x02) {
	 type_device = "MOUSE";
	 }
	 }
	 break;
	 }

     //это конструктор для класса Device (его правда нету, можно просто сетерами запихивать), запихивай в него всю инфу что вытянешь, потом выводи.
	 Device dev(desc.idProduct, desc.idVendordevice.set, type_device,
	 desc.bDeviceClass, desc.bDeviceSubClass,
	 desc.bDeviceProtocol, bInterfaceClass, bInterfaceSubClass,
	 bInterfaceProtocol);

	 }
	 }*/
	libusb_free_device_list(devs, 1);
	libusb_exit(NULL);
}

void create_devices(libusb_device *dev, vector<Device> &devices) {
	Device device;
	//находим номер шины
	uint8_t bnum = libusb_get_bus_number(dev);
	device.set_bus_number(bnum);
	//находим номер устройства
	uint8_t dnum = libusb_get_device_address(dev);
	device.set_device_number(dnum);
	libusb_device_descriptor desc;
	int r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0) {
		cout << "failed to get device descriptor" << endl;
		return;
	}
	device.set_id_vendor(desc.idVendor);
	device.set_id_product(desc.idProduct);
	string result = decryption(device.get_id_vendor(), device.get_id_product());
	device.set_decryption(result);

	//дальше идет код, который вытягивает еще больше информации из usb, если захочешь реализовать lsusb -v
	cout << "Number of possible configurations: "
			<< (int) desc.bNumConfigurations << "  ";
	cout << "Device Class: " << (int) desc.bDeviceClass << "  ";
	cout << "VendorID: " << hex << desc.idVendor << "  ";
	cout << "ProductID: " << hex << desc.idProduct << endl;
	libusb_config_descriptor *config;
	libusb_get_config_descriptor(dev, 0, &config);
	cout << "Interfaces: " << (int) config->bNumInterfaces << " ||| ";
	const libusb_interface *inter;
	const libusb_interface_descriptor *interdesc;
	const libusb_endpoint_descriptor *epdesc;
	for (int i = 0; i < (int) config->bNumInterfaces; i++) {
		inter = &config->interface[i];
		cout << "Number of alternate settings: " << inter->num_altsetting
				<< " | ";
		for (int j = 0; j < inter->num_altsetting; j++) {
			interdesc = &inter->altsetting[j];
			cout << "Interface Number: " << (int) interdesc->bInterfaceNumber
					<< " | ";
			cout << "Number of endpoints: " << (int) interdesc->bNumEndpoints
					<< " | ";
			for (int k = 0; k < (int) interdesc->bNumEndpoints; k++) {
				epdesc = &interdesc->endpoint[k];
				cout << "Descriptor Type: " << (int) epdesc->bDescriptorType
						<< " | ";
				cout << "EP Address: " << (int) epdesc->bEndpointAddress
						<< " | ";
			}
		}
	}
	devices.push_back(device);
	cout << endl << endl << endl;
	libusb_free_config_descriptor(config);
}

string decryption(uint16_t idVendor, uint16_t idProduct) {
	//код для преобразования кода продукта в 4 hex цифры.
	char buffer[16];
	sprintf(buffer, "%04x", idProduct);

	string decryption;
	string line;
	stringstream stream;

	//код для преобразования кода вендора в hex
	stream << hex << idVendor;
	string vendor(stream.str());
	stream.str("");

	//код для преобразования char* в string
	stream << buffer;
	string product;
	stream >> product;

	string regex_for_vendor_and_product = "(\\s+)([\\w\\s.]+)";
	string regexVendor = "^" + vendor + regex_for_vendor_and_product;
	string regexProduct = "\\s" + product + regex_for_vendor_and_product;
	ifstream database;
	regex vendorRegex(regexVendor);
	regex productRegex(regexProduct);
	smatch matches;
	database.open("database.txt");
	bool flag = false;
	if (database.good()) {
		while (getline(database, line)) {

			if (regex_search(line, matches, vendorRegex) && !flag) {
				cout << "Found vendor decryption\n";
				decryption = decryption + matches[2].str() + " ";
				cout << "Decryption: " << decryption << endl;
				flag = true;
			}
			if (regex_search(line, matches, productRegex) && flag) {
				cout << "Found product decryption\n";
				decryption + matches[2].str();
				decryption = decryption + matches[2].str();
				cout << "Decryption: " << decryption << endl;
				break;
			}
		}
		database.close();
	} else
		cout << "Unable to open file" << endl;
	return decryption;
}
