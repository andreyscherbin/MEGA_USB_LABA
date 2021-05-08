/*
 * names.cpp
 *
 *  Created on: 8 мая 2021 г.
 *      Author: root
 */

#include "names.h"

/*
 * Base Class
 */

#define USB_DEVICE_CLASS_AUDIO                                     0x01
#define USB_DEVICE_CLASS_COMMUNICATIONS_AND_CDC_CONTROL            0x02
#define USB_DEVICE_CLASS_HUMAN_INTERFACE_DEVICE                    0x03
#define USB_DEVICE_CLASS_PHYSICAL                                  0x05
#define USB_DEVICE_CLASS_STILL_IMAGING                             0x06
#define USB_DEVICE_CLASS_PRINTER                                   0x07
#define USB_DEVICE_CLASS_MASS_STORAGE                              0x08
#define USB_DEVICE_CLASS_HUB                                       0x09
#define USB_DEVICE_CLASS_CDC_DATA                                  0x0A
#define USB_DEVICE_CLASS_SMART_CARD                                0x0B
#define USB_DEVICE_CLASS_CONTENT_SECURITY                          0x0D
#define USB_DEVICE_CLASS_VIDEO                                     0x0E
#define USB_DEVICE_CLASS_AUDIO_VIDEO_DEVICES                       0x10
#define USB_DEVICE_CLASS_BILLBOARD_DEVICE                          0x11

int get_class_string(char *buf, size_t size, uint8_t cls) {
	const char *cp;

	if (size < 1)
		return 0;
	*buf = 0;
	switch (cls) {
	case USB_DEVICE_CLASS_AUDIO:
		cp = "Audio";
		break;
	case USB_DEVICE_CLASS_COMMUNICATIONS_AND_CDC_CONTROL:
		cp = "Communications and CDC Control";
		break;
	case USB_DEVICE_CLASS_HUMAN_INTERFACE_DEVICE:
		cp = "HID (Human Interface Device)";
		break;
	case USB_DEVICE_CLASS_PHYSICAL:
		cp = "Physical";
		break;
	case USB_DEVICE_CLASS_STILL_IMAGING:
		cp = "Image";
		break;
	case USB_DEVICE_CLASS_PRINTER:
		cp = "Printer";
		break;
	case USB_DEVICE_CLASS_MASS_STORAGE:
		cp = "Mass Storage";
		break;
	case USB_DEVICE_CLASS_HUB:
		cp = "Hub";
		break;
	case USB_DEVICE_CLASS_CDC_DATA:
		cp = "CDC data device";
		break;
	case USB_DEVICE_CLASS_SMART_CARD:
		cp = "Smart Card";
		break;
	case USB_DEVICE_CLASS_CONTENT_SECURITY:
		cp = "Content Security";
		break;
	case USB_DEVICE_CLASS_VIDEO:
		cp = "Video";
		break;
	case USB_DEVICE_CLASS_AUDIO_VIDEO_DEVICES:
		cp = "Audio/Video Devices";
		break;
	case USB_DEVICE_CLASS_BILLBOARD_DEVICE:
		cp = "Billboard Device Class";
		break;
	default:
		return 0;
		break;
	}
	return snprintf(buf, size, "%s", cp);
}

int get_subclass_string(char *buf, size_t size, uint8_t cls, uint8_t subcls) {
	const char *cp;

	if (size < 1)
		return 0;
	*buf = 0;
	switch (cls) {
	case USB_DEVICE_CLASS_HUB:
		switch (subcls) {
		case 0x00:
			cp = "";
			break;
		default:
			return 0;
			break;
		}
		break;
	case USB_DEVICE_CLASS_HUMAN_INTERFACE_DEVICE:
		switch (subcls) {
		case 0x00:
			cp = "";
			break;
		case 0x01:
			cp = "Boot Interface Subclass";
			break;
		default:
			return 0;
			break;
		}
		break;
	case USB_DEVICE_CLASS_MASS_STORAGE:
		switch (subcls) {
		case 0x01:
			cp = "Reduced Block Commands (RBC)";
			break;
		case 0x02:
			cp = "MMC (ATAPI)";
			break;
		case 0x05:
			cp = "SFF-8070i";
			break;
		case 0x06:
			cp = "SCSI transparent command set";
			break;
		default:
			return 0;
			break;
		}
		break;
	default:
		return 0;
		break;
	}
	return snprintf(buf, size, "%s", cp);
}

int get_protocol_string(char *buf, size_t size, uint8_t cls, uint8_t subcls,
		uint8_t protocol) {
	const char *cp;

	if (size < 1)
		return 0;
	*buf = 0;
	switch (cls) {
	case USB_DEVICE_CLASS_HUB:
		switch (subcls) {
		case 0x00:
			switch (protocol) {
			case 0x00:
				cp = "Full speed Hub";
				break;
			case 0x01:
				cp = "Hi-speed hub with single TT";
				break;
			case 0x02:
				cp = "Hi-speed hub with multiple TTs";
				break;
			default:
				return 0;
				break;
			}
			break;
		default:
			return 0;
			break;
		}
		break;
	case USB_DEVICE_CLASS_HUMAN_INTERFACE_DEVICE:
		switch (subcls) {
		case 0x00:
			switch (protocol) {
			case 0x00:
				cp = "None";
				break;
			case 0x01:
				cp = "Keyboard";
				break;
			case 0x02:
				cp = "Mouse";
				break;
			default:
				return 0;
				break;
			}
			break;
		case 0x01:
			switch (protocol) {
			case 0x00:
				cp = "None";
				break;
			case 0x01:
				cp = "Keyboard";
				break;
			case 0x02:
				cp = "Mouse";
				break;
			default:
				return 0;
				break;
			}
			break;
		default:
			return 0;
			break;
		}
		break;
	case USB_DEVICE_CLASS_MASS_STORAGE:
		switch (protocol) {
		case 0x50:
			cp = "Bulk-Only (BOT) Transport";
			break;
		default:
			return 0;
			break;
		}
		break;
	default:
		return 0;
		break;
	}
	return snprintf(buf, size, "%s", cp);
}

