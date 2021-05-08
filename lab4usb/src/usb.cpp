#include <string.h>
#include <libusb-1.0/libusb.h>
#include <iostream>
#include "Device.h"
#include "DeviceDescriptor.h"
#include "ConfigurationDescriptor.h"
#include "InterfaceDescriptor.h"
#include "EndpointDescriptor.h"
#include "names.h"

#include <bits/stdc++.h>
#include <regex>

#define le16_to_cpu(x) libusb_cpu_to_le16(libusb_cpu_to_le16(x))

using namespace std;

void create_devices(libusb_device *dev, vector<Device> &devices);
void get_vendor_product_string(Device &device, uint16_t idVendor,
		uint16_t idProduct);

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

	ssize_t i; 	//for iterating through the list

	for (i = 0; i < count_new; i++) {
		create_devices(devs[i], devices); //print specs of this device
	}

	printf("\n LSUSB \n\n");
	//КРАТКИЙ ВЫВОД
	for (int i = 0; i < devices.size(); i++) {
		printf("Bus %03u Device %03u: ID %04x:%04x %s %s\n",
				devices[i].getBusNumber(), devices[i].getDeviceNumber(),
				devices[i].getDeviceDescriptor().getIdVendor(),
				devices[i].getDeviceDescriptor().getIdProduct(),
				devices[i].getVendor().c_str(),
				devices[i].getProduct().c_str());
	}

	printf("\n LSUSB -v \n\n");
	//РАСШИРЕННЫЙ ВЫВОД
	for (int i = 0; i < devices.size(); i++) {
		printf("\n");
		printf("Bus %03u Device %03u: ID %04x:%04x %s %s\n",
				devices[i].getBusNumber(), devices[i].getDeviceNumber(),
				devices[i].getDeviceDescriptor().getIdVendor(),
				devices[i].getDeviceDescriptor().getIdProduct(),
				devices[i].getVendor().c_str(),
				devices[i].getProduct().c_str());

		Device device = devices[i];
		DeviceDescriptor dd = devices[i].getDeviceDescriptor();
		char cls[128], subcls[128], proto[128];
		char mfg[128] = { 0 }, prod[128] = { 0 }, serial[128] = { 0 };
		get_class_string(cls, sizeof(cls), dd.getBDeviceClass());
		get_subclass_string(subcls, sizeof(subcls), dd.getBDeviceClass(),
				dd.getBDeviceSubClass());
		get_protocol_string(proto, sizeof(proto), dd.getBDeviceClass(),
				dd.getBDeviceSubClass(), dd.getBDeviceProtocol());

		uint16_t speed = dd.getBcdUsb();
		printf("Device Descriptor:\n"
				"  bLength             %5u\n"
				"  bDescriptorType     %5u\n"
				"  bcdUSB              %2x.%02x\n"
				"  bDeviceClass        %5u %s\n"
				"  bDeviceSubClass     %5u %s\n"
				"  bDeviceProtocol     %5u %s\n"
				"  bMaxPacketSize0     %5u\n"
				"  idVendor           0x%04x %s\n"
				"  idProduct          0x%04x %s\n"
				"  bcdDevice           %2x.%02x\n"
				"  iManufacturer       %5u %s\n"
				"  iProduct            %5u %s\n"
				"  iSerial             %5u %s\n"
				"  bNumConfigurations  %5u\n", dd.getBLength(),
				dd.getBDescriptorType(), dd.getBcdUsb() >> 8,
				dd.getBcdUsb() & 0xff, dd.getBDeviceClass(), cls,
				dd.getBDeviceSubClass(), subcls, dd.getBDeviceProtocol(), proto,
				dd.getBMaxPacketSize0(), dd.getIdVendor(),
				device.getVendor().c_str(), dd.getIdProduct(),
				device.getProduct().c_str(), dd.getBcdDevice() >> 8,
				dd.getBcdDevice() & 0xff, dd.getIManufacturer(), mfg,
				dd.getIProduct(), prod, dd.getISerialNumber(), serial,
				dd.getBNumConfigurations());

		vector<ConfigurationDescriptor> configurationDescriptors =
				dd.getConfigurationDescriptors();
		for (int i = 0; i < configurationDescriptors.size(); i++) {
			ConfigurationDescriptor cd = configurationDescriptors[i];
			char *cfg = "";
			printf("  Configuration Descriptor:\n"
					"    bLength             %5u\n"
					"    bDescriptorType     %5u\n"
					"    wTotalLength       0x%04x\n"
					"    bNumInterfaces      %5u\n"
					"    bConfigurationValue %5u\n"
					"    iConfiguration      %5u %s\n"
					"    bmAttributes         0x%02x\n", cd.getBLength(),
					cd.getBDescriptorType(), le16_to_cpu(cd.getWTotalLength()),
					cd.getBNumInterfaces(), cd.getBConfigurationValue(),
					cd.getIConfiguration(), cfg, cd.getBmAttributes());

			if (!(cd.getBmAttributes() & 0x80))
				printf("      (Missing must-be-set bit!)\n");
			if (cd.getBmAttributes() & 0x40)
				printf("      Self Powered\n");
			else
				printf("      (Bus Powered)\n");
			if (cd.getBmAttributes() & 0x20)
				printf("      Remote Wakeup\n");
			if (cd.getBmAttributes() & 0x10)
				printf("      Battery Powered\n");
			printf("    MaxPower            %5umA\n",
					cd.getBMaxPower() * (speed >= 0x0300 ? 8 : 2));
			vector<InterfaceDescriptor> interfaceDescriptors =
					cd.getInterfaceDescriptors();
			for (int i = 0; i < interfaceDescriptors.size(); i++) {
				InterfaceDescriptor id = interfaceDescriptors[i];
				char cls[128], subcls[128], proto[128];
				char *ifstr = "";
				char mfg[128] = { 0 }, prod[128] = { 0 }, serial[128] = { 0 };
				get_class_string(cls, sizeof(cls), id.getBInterfaceClass());
				get_subclass_string(subcls, sizeof(subcls),
						id.getBInterfaceClass(), id.getBInterfaceSubClass());
				get_protocol_string(proto, sizeof(proto),
						id.getBInterfaceClass(), id.getBInterfaceSubClass(),
						id.getBInterfaceProtocol());
				printf("    Interface Descriptor:\n"
						"      bLength             %5u\n"
						"      bDescriptorType     %5u\n"
						"      bInterfaceNumber    %5u\n"
						"      bAlternateSetting   %5u\n"
						"      bNumEndpoints       %5u\n"
						"      bInterfaceClass     %5u %s\n"
						"      bInterfaceSubClass  %5u %s\n"
						"      bInterfaceProtocol  %5u %s\n"
						"      iInterface          %5u %s\n", id.getBLength(),
						id.getBDescriptorType(), id.getBInterfaceNumber(),
						id.getBAlternateSetting(), id.getBNumEndpoints(),
						id.getBInterfaceClass(), cls,
						id.getBInterfaceSubClass(), subcls,
						id.getBInterfaceProtocol(), proto, id.getIInterface(),
						ifstr);
				vector<EndpointDescriptor> endpointDescriptors =
						id.getEndpointDescriptors();
				for (int i = 0; i < endpointDescriptors.size(); i++) {
					EndpointDescriptor ed = endpointDescriptors[i];
					static const char *const typeattr[] = { "Control",
							"Isochronous", "Bulk", "Interrupt" };
					static const char *const syncattr[] = { "None",
							"Asynchronous", "Adaptive", "Synchronous" };
					static const char *const usage[] = { "Data", "Feedback",
							"Implicit feedback Data", "(reserved)" };
					static const char *const hb[] =
							{ "1x", "2x", "3x", "(?\?)" };
					const unsigned char *buf;
					unsigned size;
					unsigned wmax = le16_to_cpu(ed.getWMaxPacketSize());

					printf("      Endpoint Descriptor:\n"
							"        bLength             %5u\n"
							"        bDescriptorType     %5u\n"
							"        bEndpointAddress     0x%02x  EP %u %s\n"
							"        bmAttributes        %5u\n"
							"          Transfer Type            %s\n"
							"          Synch Type               %s\n"
							"          Usage Type               %s\n"
							"        wMaxPacketSize     0x%04x  %s %d bytes\n"
							"        bInterval           %5u\n",
							ed.getBLength(), ed.getBDescriptorType(),
							ed.getBEndpointAddress(),
							ed.getBEndpointAddress() & 0x0f,
							(ed.getBEndpointAddress() & 0x80) ? "IN" : "OUT",
							ed.getBmAttributes(),
							typeattr[ed.getBmAttributes() & 3],
							syncattr[(ed.getBmAttributes() >> 2) & 3],
							usage[(ed.getBmAttributes() >> 4) & 3], wmax,
							hb[(wmax >> 11) & 3], wmax & 0x7ff,
							ed.getBInterval());
				}
			}

		}
	}
	libusb_free_device_list(devs, 1);
	libusb_exit(NULL);
}

void create_devices(libusb_device *dev, vector<Device> &devices) {
	Device device;
	DeviceDescriptor deviceDescriptor = device.getDeviceDescriptor();

	//находим номер шины
	uint8_t bnum = libusb_get_bus_number(dev);
	device.setBusNumber(bnum);
	//находим номер устройства
	uint8_t dnum = libusb_get_device_address(dev);
	device.setDeviceNumber(dnum);
	libusb_device_descriptor desc;
	int r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0) {
		cout << "failed to get device descriptor" << endl;
		return;
	}

	//DeviceDescriptor
	deviceDescriptor.setBLength(desc.bLength);
	deviceDescriptor.setBDescriptorType(desc.bDescriptorType);
	deviceDescriptor.setBcdUsb(desc.bcdUSB);
	deviceDescriptor.setBDeviceClass(desc.bDeviceClass);
	deviceDescriptor.setBDeviceSubClass(desc.bDeviceSubClass);
	deviceDescriptor.setBDeviceProtocol(desc.bDeviceProtocol);
	deviceDescriptor.setBMaxPacketSize0(desc.bMaxPacketSize0);
	deviceDescriptor.setIdVendor(desc.idVendor);
	deviceDescriptor.setIdProduct(desc.idProduct);
	deviceDescriptor.setBcdDevice(desc.bcdDevice);
	deviceDescriptor.setIManufacturer(desc.iManufacturer);
	deviceDescriptor.setIProduct(desc.iProduct);
	deviceDescriptor.setISerialNumber(desc.iSerialNumber);
	deviceDescriptor.setBNumConfigurations(desc.bNumConfigurations);

	get_vendor_product_string(device, desc.idVendor, desc.idProduct);

	libusb_config_descriptor *config;
	libusb_get_config_descriptor(dev, 0, &config);

	//ConfigurationDescriptor
	ConfigurationDescriptor configurationDescriptor;
	configurationDescriptor.setBLength(config->bLength);
	configurationDescriptor.setBDescriptorType(config->bDescriptorType);
	configurationDescriptor.setWTotalLength(config->wTotalLength);
	configurationDescriptor.setBNumInterfaces(config->bNumInterfaces);
	configurationDescriptor.setBConfigurationValue(config->bConfigurationValue);
	configurationDescriptor.setIConfiguration(config->iConfiguration);
	configurationDescriptor.setBmAttributes(config->bmAttributes);
	configurationDescriptor.setBMaxPower(config->MaxPower);

	const libusb_interface *inter;
	const libusb_interface_descriptor *interdesc;
	const libusb_endpoint_descriptor *epdesc;
	for (int i = 0; i < (int) config->bNumInterfaces; i++) {
		inter = &config->interface[i];
		for (int j = 0; j < inter->num_altsetting; j++) {
			interdesc = &inter->altsetting[j];
			//InterfaceDescriptor
			InterfaceDescriptor interfaceDescriptor;
			interfaceDescriptor.setBLength(interdesc->bLength);
			interfaceDescriptor.setBDescriptorType(interdesc->bDescriptorType);
			interfaceDescriptor.setBInterfaceNumber(
					interdesc->bInterfaceNumber);
			interfaceDescriptor.setBAlternateSetting(
					interdesc->bAlternateSetting);
			interfaceDescriptor.setBNumEndpoints(interdesc->bNumEndpoints);
			interfaceDescriptor.setBInterfaceClass(interdesc->bInterfaceClass);
			interfaceDescriptor.setBInterfaceSubClass(
					interdesc->bInterfaceSubClass);
			interfaceDescriptor.setBInterfaceProtocol(
					interdesc->bInterfaceProtocol);
			interfaceDescriptor.setIInterface(interdesc->iInterface);

			for (int k = 0; k < (int) interdesc->bNumEndpoints; k++) {
				epdesc = &interdesc->endpoint[k];
				//EndpointDescriptor
				EndpointDescriptor endpointDescriptor;
				endpointDescriptor.setBLength(epdesc->bLength);
				endpointDescriptor.setBDescriptorType(epdesc->bDescriptorType);
				endpointDescriptor.setBEndpointAddress(
						epdesc->bEndpointAddress);
				endpointDescriptor.setBmAttributes(epdesc->bmAttributes);
				endpointDescriptor.setWMaxPacketSize(epdesc->wMaxPacketSize);
				endpointDescriptor.setBInterval(epdesc->bInterval);
				interfaceDescriptor.getEndpointDescriptors().push_back(
						endpointDescriptor);
			}
			configurationDescriptor.getInterfaceDescriptors().push_back(
					interfaceDescriptor);
		}
	}
	deviceDescriptor.getConfigurationDescriptors().push_back(
			configurationDescriptor);
	device.setDeviceDescriptor(deviceDescriptor);
	devices.push_back(device);
	cout << endl << endl << endl;
	libusb_free_config_descriptor(config);
}

void get_vendor_product_string(Device &device, uint16_t idVendor,
		uint16_t idProduct) {
	//код для преобразования кода продукта в 4 hex цифры.
	char buffer[16];
	sprintf(buffer, "%04x", idProduct);

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
				device.setVendor(matches[2].str());
				flag = true;
			}
			if (regex_search(line, matches, productRegex) && flag) {
				device.setProduct(matches[2].str());
				break;
			}
		}
		database.close();
	} else
		cout << "Unable to open file" << endl;
}
