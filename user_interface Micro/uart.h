 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/**********************************************************
 *                  CONFIGRATION PARAMETERS
 ******************************************************/

typedef enum
{
	BIT_5=0 ,BIT_6=1,BIT_7=2,BIT_8=3,BIT_9=4
}data;

typedef enum
{
	NO_PARITY=0,EVEN_PARITY=2,ODD_PARITY=3
}parity;

typedef enum
{
	BIT_1=0,BIT_2=1
}stop;

typedef struct
{
	data DATA_MOOD;
	parity PARITY_MOOD;
	stop STOP_MOOD;
	uint32 BAULD;
}UART_config;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(UART_config* config);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
