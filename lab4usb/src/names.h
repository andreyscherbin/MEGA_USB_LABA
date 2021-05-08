/*
 * names.h
 *
 *  Created on: 8 мая 2021 г.
 *      Author: root
 */

#include <iostream>
#ifndef NAMES_H_
#define NAMES_H_


extern int get_class_string(char *buf, size_t size, uint8_t cls);
extern int get_subclass_string(char *buf, size_t size, uint8_t cls, uint8_t subcls);
extern int get_protocol_string(char *buf, size_t size, uint8_t cls, uint8_t subcls, uint8_t protocol);


#endif /* NAMES_H_ */
