/*
 * password.h
 *
 *  Created on: Nov 6, 2021
 *      Author: Kyrillos
 */

#ifndef PASSWORD_H_
#define PASSWORD_H_

#include"std_types.h"

#define READY  0x10
#define DONE   0x20
#define RIGHT  0x30
#define WRONG  0x40
#define OPEN   0x50
#define OPENED 0x60
#define CLOSE  0x70
#define FIRST 0x9
#define NOT_FIRST 0x8


void PASSWORD_storePass();

void PASSWORD_checkPass();

#endif /* PASSWORD_H_ */
